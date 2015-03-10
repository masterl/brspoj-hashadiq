#include <iostream>
#include <string>
#include <memory>
#include <vector>

using namespace std;

/*  Neste problema, pede-se para armazenar, gerenciar e buscar por 
    indivíduos definidos por
        um identificador único (inteiro) 
        Primeiro nome
        último nome,
        data de nascimento
        telefone. 
*/
struct Person
{
    Person( int _id = 0,
            const string &_first_name = "",
            const string &_last_name = "",
            const string &_birthday = "",
            const string &_phone = ""):
        id(_id),
        first_name(_first_name),
        last_name(_last_name),
        birthday(_birthday),
        phone(_phone)
        {
        }
    int id;
    string first_name;
    string last_name;
    string birthday;
    string phone;
    shared_ptr<Person> fn_collision;
    shared_ptr<Person> ln_collision;
    shared_ptr<Person> birth_collision;
    shared_ptr<Person> phone_collision;

    void print(void)
    {
        cout   << "\n      Id: " << id
                    << "\n   First: " << first_name
                    << "\n    Last: " << last_name
                    << "\nBirthday: " << birthday
                    << "\n   Phone: " << phone
                    << endl;
    }
};

typedef shared_ptr<Person> Person_ptr;
typedef vector<Person_ptr> HashTable;

class PersonManager
{
    public:
        PersonManager(void):
            max_elements(503),
            id_table(max_elements),
            fn_table(max_elements),
            ln_table(max_elements),
            birth_table(max_elements),
            phone_table(max_elements)
        {
        }

        void execute(string line)
        {
            unsigned int first_space = line.find(" ");
            string args = line.substr(first_space+1);
            string function = line.erase(first_space);

            cout << "\nfunction: [" << function << "]" << endl;
            cout << "args: [" << args << "]" << endl;

            if(!function.compare("add"))
            {
                //Example: 123 Roberto Nascimento 01/01/1960 +55-21-0190-0190

                vector<string> params;
                split_params(params,args);

                // for(auto param : params)
                // {
                //     cout << "\n[" << param << "]";
                // }
                // cout << endl;

                if(params.size() == 5)
                {
                    add(stoi(params[0]),params[1],params[2],params[3],params[4]);
                }
            }
            else if(!function.compare("del"))
            {
                // assumed to be a number
                del(stoi(args));
            }
            else if(!function.compare("info"))
            {
                // assumed to be a number
                info(stoi(args));
            }
            else if(!function.compare("query"))
            {
                query(args);
            }
        }
    private:
        const unsigned int max_elements; // Large prime number chosen
        HashTable id_table;
        HashTable fn_table;
        HashTable ln_table;
        HashTable birth_table;
        HashTable phone_table;

        /*  somente imprime na saída quando ocorre erro na inserção de um individuo,
            ocorrida na inserção de individuo com identificador duplicado.
        */
        void add(int id,
            const string &first_name,
            const string &last_name,
            const string &birthday,
            const string &phone)
        {
            if((id < 0) || (id > max_elements))
            {
                cout << "invalid id" << endl;
                return;
            }

            if(id_table[id] != NULL)
            {
                cout << "ID " << id << " ja cadastrado." << endl;
            }

            shared_ptr<Person> person(new Person(id,first_name,last_name,birthday,phone));

            // cout << "adding " << endl;
            // person->print();

            id_table[id] = person;

            unsigned int hash_number = hash(first_name);

            insert_on_fn_table(person,hash_number);

            hash_number = hash(last_name);
            insert_on_ln_table(person,hash_number);

            hash_number = hash(birthday);
            insert_on_birth_table(person,hash_number);

            hash_number = hash(phone);
            insert_on_phone_table(person,hash_number);
        }

        /*  O comando ''del'' remove todos dados relacionados a um determinado identificador,
            e retorna erro se não existir individuo com o identificador fornecido.
        */
        void del(int id)
        {
            if((id < 0) || (id > max_elements) || (id_table[id] == NULL))
            {
                cout << "ID " << id << " nao existente" << endl;
                return;
            }

            cout << "id_table: " << id_table[id].get() << endl;
            id_table[id]->print();

            remove_from_fn_table(id_table[id],hash(id_table[id]->first_name));
            remove_from_ln_table(id_table[id],hash(id_table[id]->last_name));
            remove_from_birth_table(id_table[id],hash(id_table[id]->birthday));
            remove_from_phone_table(id_table[id],hash(id_table[id]->phone));
            id_table[id].reset();
        }

        void info(int id)
        {
            if((id < 0) || (id > max_elements) || (id_table[id] == NULL))
            {
                cout << "ID " << id << " nao existente." << endl;
                return;
            }

            cout << id_table[id]->first_name << " "
                      << id_table[id]->last_name << " "
                      << id_table[id]->birthday << " "
                      << id_table[id]->phone << endl;
        }

        /*  O comando ''query'' realiza uma busca nos indivíduos cadastrados.
            Conforme as seguintes tags de busca:

            fn: Primeiro nome
            ln: Ultimo nome
            bd: Data de nascimento
            pn: Telefone
        */
        void query(const string &query_str)
        {
            cout << "Entrou na query" << endl;
        }

        

        void insert_on_fn_table(Person_ptr person,unsigned int hash_number)
        {
            if(fn_table[hash_number] != NULL)
            {
                person->fn_collision = fn_table[hash_number];
            }

            fn_table[hash_number] = person;
        }

        void insert_on_ln_table(Person_ptr person,unsigned int hash_number)
        {
            if(ln_table[hash_number] != NULL)
            {
                person->ln_collision = ln_table[hash_number];
            }

            ln_table[hash_number] = person;
        }

        void insert_on_birth_table(Person_ptr person,unsigned int hash_number)
        {
            if(birth_table[hash_number] != NULL)
            {
                person->birth_collision = birth_table[hash_number];
            }

            birth_table[hash_number] = person;
        }

        void insert_on_phone_table(Person_ptr person,unsigned int hash_number)
        {
            if(phone_table[hash_number] != NULL)
            {
                person->phone_collision = phone_table[hash_number];
            }

            phone_table[hash_number] = person;
        }

        void remove_from_fn_table(Person_ptr person,unsigned int hash_number)
        {
            cout << "remove_from_fn_table [" << hash_number << "]" << endl;
            if(fn_table[hash_number] != NULL)
            {
                cout << "found" << endl;
                Person_ptr last_person;
                Person_ptr people_itr = fn_table[hash_number];
                do
                {
                    cout    << "people id: " << people_itr->id
                            << "\nperson id: " << person->id << endl;
                    if(people_itr->id == person->id)
                    {
                        break;
                    }
                    last_person = people_itr;
                    people_itr = people_itr->fn_collision;
                }while(people_itr != NULL);
                cout << "people_itr " << people_itr.get() << endl;

                cout << "removing..." << endl;
                if(last_person != NULL)
                //if((last_person != NULL) && (people_itr != NULL))
                {
                    cout << "last person present" << endl;
                    last_person->print();
                    last_person->fn_collision = people_itr->fn_collision;
                    //people_itr.reset();
                }
                else if(fn_table[hash_number]->fn_collision != NULL)
                {
                    cout << "single element" << endl;
                    fn_table[hash_number] = fn_table[hash_number]->fn_collision;
                }
            }
        }

        void remove_from_ln_table(Person_ptr person,unsigned int hash_number)
        {
            cout << "remove_from_ln_table [" << hash_number << "]" << endl;
            if(ln_table[hash_number] != NULL)
            {
                cout << "found" << endl;
                Person_ptr last_person;
                Person_ptr people_itr = ln_table[hash_number];
                do
                {
                    cout    << "people id: " << people_itr->id
                            << "\nperson id: " << person->id << endl;
                    if(people_itr->id == person->id)
                    {
                        break;
                    }
                    last_person = people_itr;
                    people_itr = people_itr->ln_collision;
                }while(people_itr != NULL);
                cout << "people_itr " << people_itr.get() << endl;

                cout << "removing..." << endl;
                if(last_person != NULL)
                //if((last_person != NULL) && (people_itr != NULL))
                {
                    cout << "last person present" << endl;
                    last_person->print();
                    last_person->ln_collision = people_itr->ln_collision;
                    //people_itr.reset();
                }
                else if(ln_table[hash_number]->ln_collision != NULL)
                {
                    cout << "single element" << endl;
                    ln_table[hash_number] = ln_table[hash_number]->ln_collision;
                }
            }
        }

        void remove_from_birth_table(Person_ptr person,unsigned int hash_number)
        {
            cout << "remove_from_birth_table [" << hash_number << "]" << endl;
            if(birth_table[hash_number] != NULL)
            {
                cout << "found" << endl;
                Person_ptr last_person;
                Person_ptr people_itr = birth_table[hash_number];
                do
                {
                    cout    << "people id: " << people_itr->id
                            << "\nperson id: " << person->id << endl;
                    if(people_itr->id == person->id)
                    {
                        break;
                    }
                    last_person = people_itr;
                    people_itr = people_itr->birth_collision;
                }while(people_itr != NULL);
                cout << "people_itr " << people_itr.get() << endl;

                cout << "removing..." << endl;
                if(last_person != NULL)
                //if((last_person != NULL) && (people_itr != NULL))
                {
                    cout << "last person present" << endl;
                    last_person->print();
                    last_person->birth_collision = people_itr->birth_collision;
                    //people_itr.reset();
                }
                else if(birth_table[hash_number]->birth_collision != NULL)
                {
                    cout << "single element" << endl;
                    birth_table[hash_number] = birth_table[hash_number]->birth_collision;
                }
            }
        }

        void remove_from_phone_table(Person_ptr person,unsigned int hash_number)
        {
            cout << "remove_from_phone_table [" << hash_number << "]" << endl;
            if(phone_table[hash_number] != NULL)
            {
                cout << "found" << endl;
                Person_ptr last_person;
                Person_ptr people_itr = phone_table[hash_number];
                do
                {
                    cout    << "people id: " << people_itr->id
                            << "\nperson id: " << person->id << endl;
                    if(people_itr->id == person->id)
                    {
                        break;
                    }
                    last_person = people_itr;
                    people_itr = people_itr->phone_collision;
                }while(people_itr != NULL);
                cout << "people_itr " << people_itr.get() << endl;

                cout << "removing..." << endl;
                if(last_person != NULL)
                //if((last_person != NULL) && (people_itr != NULL))
                {
                    cout << "last person present" << endl;
                    last_person->print();
                    last_person->phone_collision = people_itr->phone_collision;
                    //people_itr.reset();
                }
                else if(phone_table[hash_number]->phone_collision != NULL)
                {
                    cout << "single element" << endl;
                    phone_table[hash_number] = phone_table[hash_number]->phone_collision;
                }
            }
        }

        void split_params(vector<string> &params,const string &params_str)
        {
            unsigned int i;
            params.clear();
            params.push_back(string());

            for(i = 0; i < params_str.size(); ++i)
            {
                if(params_str[i] == ' ')
                {
                    params.push_back(string());
                }
                else
                {
                    params.back() += params_str[i];
                }
            }
        }

        unsigned int hash(const string &str)
        {
            unsigned int hash_number = 0;
            unsigned int mult = 1;

            for(char c : str)
            {
                hash_number += c * mult;
                ++mult;
            }

            cout << "hashing [" << str << "] - [" << (hash_number % max_elements) << "]" << endl;

            return hash_number % max_elements;
        }
};

int main(void)
{
    char input[2048];
    unsigned int chars_read;
    PersonManager manager;

    do
    {
        cin.getline(input,2048);
        chars_read = cin.gcount();
        input[chars_read] = '\0';
        if(chars_read > 0)
        {
            manager.execute(input);
        }
    }while(chars_read > 0);

    // testing execution time
    // for(int i = 0; i < 50000; i++)
    // {
    //     for(int j = 0; j < 500; j++);
    // }

    return 0;
}
