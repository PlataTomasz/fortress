#if !defined(RESPONSIBILITY_CHAIN_HPP)
#define RESPONSIBILITY_CHAIN_HPP

/**
 * Generic Responsiblity Chain Link class - RCL
*/
template<class RetType>
class RCL
{
protected:
    //NOTE: Currently identifier doesn't need to be unique, but if 2 links have the same identifier, the eariel will have priority
    String identifier;

    RCL<RetType>* prev = nullptr;
    RCL<RetType>* next = nullptr;
    /**
     * Internal logic for current responsibility chain link evaluation step. Override it for your use.
    */
    virtual RetType evaluate_impl() = 0;
public:
    RetType evaluate()
    {
        if(RetType result = this->execute_impl())
        {
            if(next != nullptr)
            {
                return this->next->execute();
            }
            else
            {
                //No next link in chain - everything went right
                return 0;
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
    RCL<RetType>* set_next(RCL<RetType>* new_next)
    {
        this->next = new_next
        this->next->prev = this;

        return new_next;
    }

    /**
     * Adds new link to responsibility chain. Unlike set_next() method, this adds new link between this and next.
    */
    void add_next_link(RCL<RetType>* added)
    {
        if(!this->is_last_link())
        {
            //Current value of next pointer
            RCL<RetType>* old_next = this->next;
            RCL<RetType>* last_added_link = added->get_last_link();

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

    void add_prev_link(RCL<RetType>* added)
    {
        if(!this->is_first_link())
        {
            //Current value of prev pointer
            RCL<RetType>* old_prev = this->prev;
            RCL<RetType>* last_added_link = added->get_last_link();

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
    RCL<RetType>* set_prev(RCL<T>* new_prev)
    {
        this->prev = new_prev;
        this->prev->next = this;

        return new_prev;
    }

    RCL<RetType>* get_first_link()
    {
        RCL<RetType>* link = this->prev;

        //Iterate through this->prev
        while(link != nullptr)
        {
            link = link->prev;
        }

        return link;
    }

    RCL<RetType>* get_last_link()
    {
        //Iterate through this->next
        RCL<RetType>* link = this->next;

        while(link != nullptr)
        {
            link = link->prev;
        }

        return link;
    }

    /**
     * Finds responsibility chain link based on It's identifier.
    */
    RCL<RetType>* find_link(String identifier)
    {
        RCL<RetType>* first = this->get_first_link();
        RCL<RetType>* link = this->next;

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

    RCL(String identifier)
    {
        this->identifier = identifier;
    }
};

#endif // RESPONSIBILITY_CHAIN_HPP
