#pragma once

class Controler{
    public:
        Controler(){};
        ~Controler(){};
        void execAction()const ;
        static void canSniffer();
    private:
        //char** createArgumentTable(vector<string> argV); 
};