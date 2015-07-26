
#ifndef Command_h
#define Command_h
 
 class Command {
  protected:
    String name;
    Command *commandParent;
    
  public:   
    virtual String createCommand(int state) = 0;
    virtual String createCommand() = 0;
    virtual void setParent(Command *room) {this->commandParent = room;} ;
    virtual String getObjectName(){ return name;};
 };

 #endif
