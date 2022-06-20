#include <iostream>
#include<cstring>

class Detail
{

private:
    char *code, *name, *measure_unit;
    int value;

public:
    Detail(const char * code, const char * name, const char * measure_unit, int value)
    {
        this->code = new char[strlen(code + 1)];
        std::strcpy(this->code, code);

        this->name = new char[strlen(name + 1)];
        std::strcpy(this->name, name);

        this->measure_unit = new char[strlen(measure_unit + 1)];
        std::strcpy(this->measure_unit, measure_unit);

        this->value = value;
    }

    ~Detail()
    {
        delete []name;
        delete []code;
        delete []measure_unit;
    }

    const char * get_code(){ return code; }

    const char * get_name(){ return name; }

    const char * get_measure_unit(){ return measure_unit; }

    int get_value() const{ return value; }

    int cmp_details(Detail * other)
    {
        return value == other->get_value() && !strcmp(name, other->get_name()) && !strcmp(code, other->code) && !strcmp(measure_unit, other->measure_unit);
    }

};


struct Element : public Detail
{
private:
    Element *random, *next;

public:
    Element(Element *next, Element *random, char *code, char *name, char *measure_unit, int value) : Detail(code, name, measure_unit, value), next(next), random(random) { }

    ~Element() { }

    Element *get_next(){ return this->next; }

    void set_next(Element *next){ this->next = next; }

    void print_element()
    {
        printf(" code: %s\n name: %s\n measure unit: %s\n value: %d\n", this->get_code(), this->get_name(), this->get_measure_unit(), this->get_value());
    }

};

class List
{

private:
    Element *begin, *current;

public:
    List()
    {
        this->begin = nullptr;
        this->current = nullptr;
    }

    List(Element *begin, Element *current) : begin(begin), current(current) { }

    ~List()
    {
        for(Element *curr = begin, *last = nullptr;last != current;last = curr, curr = curr->get_next())
            delete []curr;
    }

    Element *get_first_element()
    {
        return begin;
    }

    void add_element(Element *new_element)
    {
        if(!begin && !current)
            this->begin = new_element;
        else
            this->current->set_next(new_element);

        Element *curr;
        for(curr = new_element; curr->get_next(); curr = curr->get_next());

        this->current = curr;
    }

    void print_list()
    {
        int index = 0;
        for (Element *curr = begin, *last = nullptr; last != current; last = curr, curr = curr->get_next())
        {
            printf("%d\n", index++);
            curr->print_element();
            printf("\n");
        }
    }

    int delete_element(Detail *delete_)
    {
        for(Element *curr = begin, *last = nullptr;last != current;last = curr, curr = curr->get_next())
            if(curr != nullptr && delete_ != nullptr && curr->cmp_details(delete_))
            {
                if(last != nullptr)
                    last->set_next(curr->get_next());

                else
                    this->begin = curr->get_next();


                delete curr;
                curr = nullptr;
                return 1;
            }

        return 0;
    }

    Element * find_element(Detail *find)
    {
        for(Element *curr = begin, *last = nullptr;last != current;last = curr, curr = curr->get_next())
            if(curr->cmp_details(find))
                return curr;

        return nullptr;
    }

};


int main()
{
    List l;

    Element *e1 = new Element(nullptr, nullptr, "1", "1", "1", 1);
    Element *e2 =  new Element(nullptr, nullptr, "2", "2", "2", 2);
    Element *e3 =  new Element(nullptr, nullptr, "3", "3", "3", 3);

    l.add_element(e1);
    l.add_element(e2);
    l.add_element(e3);
    l.print_list();

    Detail *d1 = new Detail("1", "1", "1", 1);
    l.delete_element(d1);
    l.print_list();

    Detail *d2 = new Detail("2", "2", "2", 2);
    Element *find = l.find_element(d1);
    Element *find1 = l.find_element(d2);

    return 0;
}
