#include <iostream>
#include <string>
#include <memory>
#include <vector>

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
            const std::string &_first_name = "",
            const std::string &_last_name = "",
            const std::string &_birthday = "",
            const std::string &_phone = ""):
        id(_id),
        first_name(_first_name),
        last_name(_last_name),
        birthday(_birthday),
        phone(_phone)
        {
        }
    int id;
    std::string first_name;
    std::string last_name;
    std::string birthday;
    std::string phone;
    std::shared_ptr<Person> collision;
};

typedef std::shared_ptr<Person> Person_ptr;
typedef std::vector<Person_ptr> HashTable;


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

        /*  somente imprime na saída quando ocorre erro na inserção de um individuo,
            ocorrida na inserção de individuo com identificador duplicado.
        */
        void add(int id,
            const std::string &first_name,
            const std::string &last_name,
            const std::string &birthday,
            const std::string &phone)
        {
            if((id < 0) || (id > max_elements))
            {
                std::cout << "invalid id" << std::endl;
                return;
            }

            if(id_table[id] != NULL)
            {
                std::cout << "ID " << id << " ja cadastrado." << std::endl;
            }

            std::shared_ptr<Person> person(new Person(id,first_name,last_name,birthday,phone));

            id_table[id] = person;

            unsigned int hash_number = hash(first_name);

            insert_on_table(fn_table,person,hash_number);

            hash_number = hash(last_name);
            insert_on_table(ln_table,person,hash_number);

            hash_number = hash(birthday);
            insert_on_table(birth_table,person,hash_number);

            hash_number = hash(phone);
            insert_on_table(phone_table,person,hash_number);
        }

        /*  O comando ''del'' remove todos dados relacionados a um determinado identificador,
            e retorna erro se não existir individuo com o identificador fornecido.
        */
        void del(int id)
        {
            if((id < 0) || (id > max_elements) || (id_table[id] == NULL))
            {
                std::cout << "ID " << id << " nao existente" << std::endl;
                return;
            }

            remove_from_table(fn_table,id_table[id],hash(id_table[id]->first_name));
            remove_from_table(ln_table,id_table[id],hash(id_table[id]->last_name));
            remove_from_table(birth_table,id_table[id],hash(id_table[id]->birthday));
            remove_from_table(phone_table,id_table[id],hash(id_table[id]->phone));
            id_table[id].reset();
        }

        void info(int id)
        {
            if((id < 0) || (id > max_elements) || (id_table[id] == NULL))
            {
                std::cout << "ID " << id << " nao existente." << std::endl;
                return;
            }

            std::cout << id_table[id]->first_name << " "
                      << id_table[id]->last_name << " "
                      << id_table[id]->birthday << " "
                      << id_table[id]->phone << std::endl;
        }
    private:
        const unsigned int max_elements; // Large prime number chosen
        HashTable id_table;
        HashTable fn_table;
        HashTable ln_table;
        HashTable birth_table;
        HashTable phone_table;


        unsigned int hash(const std::string &str)
        {
            unsigned int hash_number = 0;
            unsigned int mult = 1;

            for(char c : str)
            {
                hash_number += c * mult;
                ++mult;
            }

            return hash_number % max_elements;
        }

        void insert_on_table(HashTable &table,Person_ptr person,unsigned int hash_number)
        {
            if(table[hash_number] != NULL)
            {
                person->collision = table[hash_number];
            }

            table[hash_number] = person;
        }

        void remove_from_table(HashTable &table,Person_ptr person,unsigned int hash_number)
        {
            if(table[hash_number] != NULL)
            {
                Person_ptr last_person;
                Person_ptr people_itr = table[hash_number];
                do
                {
                    if(people_itr->id == person->id)
                    {
                        break;
                    }
                    last_person = people_itr;
                    people_itr = people_itr->collision;
                }while(people_itr != NULL);

                if(last_person != NULL)
                {
                    last_person->collision = people_itr->collision;
                    people_itr.reset();
                }
                else
                {
                    table[hash_number] = table[hash_number]->collision;
                }
            }
        }
};

int main(void)
{
    return 0;
}
