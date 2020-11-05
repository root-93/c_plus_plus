#pragma once

class Command{
    public:
        virtual         ~Command(){}
        virtual void    execute()const = 0;
        virtual void    execute(char key)const = 0;
    
        
    protected:
                        Command(){}
    

};