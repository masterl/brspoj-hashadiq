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
            fn_table(max_elements),
            ln_table(max_elements),
            birth_table(max_elements),
            phone_table(max_elements)
        {
        }
        void add(int id,
            const std::string &first_name,
            const std::string &last_name,
            const std::string &birthday,
            const std::string &phone)
        {
            std::shared_ptr<Person> person(new Person(id,first_name,last_name,birthday,phone));

            unsigned int hash_number = hash(first_name);

            insert_on_table(fn_table,person,hash_number);

            hash_number = hash(last_name);
            insert_on_table(ln_table,person,hash_number);

            hash_number = hash(birthday);
            insert_on_table(birth_table,person,hash_number);

            hash_number = hash(phone);
            insert_on_table(phone_table,person,hash_number);
        }
    private:
        const unsigned int max_elements; // Large prime number chosen
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
};

int main(void)
{
    return 0;
}
