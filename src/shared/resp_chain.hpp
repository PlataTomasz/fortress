#if !defined(RESPONSIBILITY_CHAIN_HPP)
#define RESPONSIBILITY_CHAIN_HPP

#include <variant/string.hpp>

/**
 * Generic Responsiblity Chain Link class - RCL
*/
template<typename RetType, typename ArgType>
class RCL
{
protected:
    //NOTE: Currently identifier doesn't need to be unique, but if 2 links have the same identifier, the eariel will have priority
    String identifier;

    RCL<RetType, ArgType>* prev = nullptr;
    RCL<RetType, ArgType>* next = nullptr;
    /**
     * Internal logic for current responsibility chain link evaluation step. Override it for your use.
    */
    virtual RetType evaluate_impl(ArgType data) = 0;
public:
    RetType evaluate(ArgType data)
    {
        if(RetType result = this->evaluate_impl(data))
        {
            if(next != nullptr)
            {
                return this->next->evaluate(data);
            }
            else
            {
                //No next link in chain - everything went right
                return static_cast<RetType>(0);
            }
        }
        else
        {
            return result;
        }
    }

    bool is_first_link()
    {
        return this->prev == nullptr;
    }

    bool is_last_link()
    {
        return this->next == nullptr;
    }

    /**
     * Replaces next link in responsibility chain with new one without any connection to previous ones
    */
    RCL<RetType, ArgType>* set_next(RCL<RetType, ArgType>* new_next)
    {
        this->next = new_next;
        this->next->prev = this;

        return new_next;
    }

    /**
     * Adds new link to responsibility chain. Unlike set_next() method, this adds new link between this and next.
    */
    void add_next_link(RCL<RetType, ArgType>* added)
    {
        if(!this->is_last_link())
        {
            //Current value of next pointer
            RCL<RetType, ArgType>* old_next = this->next;
            RCL<RetType, ArgType>* last_added_link = added->get_last_link();

            this->next = added;
            this->next->prev = this;

            last_added_link->next = old_next;
            old_next->prev = last_added_link;
        }
        else
        {
            //Just set new next link since it doesn't exist already
            this->set_next(added);
        }
    }

    void add_prev_link(RCL<RetType, ArgType>* added)
    {
        if(!this->is_first_link())
        {
            //Current value of prev pointer
            RCL<RetType, ArgType>* old_prev = this->prev;
            RCL<RetType, ArgType>* last_added_link = added->get_last_link();

            old_prev->next = added;
            added->prev = old_prev;

            this->prev = last_added_link;
            last_added_link->next = this;
        }
        else
        {
            //Just set new next link since it doesn't exist already
            this->set_prev(added);
        }
    }

    /**
     * Replaces previous link in responsibility chain with new one without any connection to previous ones
    */
    RCL<RetType, ArgType>* set_prev(RCL<RetType, ArgType>* new_prev)
    {
        this->prev = new_prev;
        this->prev->next = this;

        return new_prev;
    }

    RCL<RetType, ArgType>* get_first_link()
    {
        RCL<RetType, ArgType>* link = this->prev;

        //Iterate through this->prev
        while(link != nullptr)
        {
            link = link->prev;
        }

        return link;
    }

    RCL<RetType, ArgType>* get_last_link()
    {
        //Iterate through this->next
        RCL<RetType, ArgType>* link = this->next;

        while(link != nullptr)
        {
            link = link->prev;
        }

        return link;
    }

    /**
     * Finds responsibility chain link based on It's identifier.
    */
    RCL<RetType, ArgType>* find_link(String identifier)
    {
        RCL<RetType, ArgType>* first = this->get_first_link();
        RCL<RetType, ArgType>* link = this->next;

        while(link != nullptr)
        {
            if(this->identifier == identifier)
            {
                return link;
            }
            else
            {
                link = this->next;
            }
        }

        return link;
    }

    /**
     * Destroys each RCL objects starting from this object
    */
    void destroy_chain()
    {
        RCL<RetType, ArgType> current_link = this->get_last_link();

        while(current_link != this->next)
        {
            RCL<RetType, ArgType> tmp = current_link->prev;
            delete current_link;

            //Move to previous link
            current_link = tmp;
        }
        
        //Ensure that this RCL object will be deleted as last
        delete this;
    }

    RCL(String identifier)
    {
        this->identifier = identifier;
    }

    virtual ~RCL()
    {

    }
};

#endif // RESPONSIBILITY_CHAIN_HPP
