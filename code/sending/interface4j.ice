module sending
{
    module server
    {
        struct Command
        {
            string id;
            int type;
        };

        struct Rtn
        {
            int e;
            string str;
        };

        interface Api
        {
            Rtn push(Command m);
        };
    };
};