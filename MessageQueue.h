//MessageQueue.h

//actually a linked list
class MessageQueue
{
    public:
        void enqueue();
        void dequeue();

    private:
    
        std::list<String> queue;
};
