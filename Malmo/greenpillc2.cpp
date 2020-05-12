
// Malmo:

#include <AgentHost.h>
#include <ClientPool.h>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>
using namespace malmo;

// STL:
#include <cstdlib>
#include <exception>
#include <iostream>
using namespace std;

vector<string> GetItems(WorldState world_state,std::stringstream & ss, boost::property_tree::ptree & pt)
{
    vector<string> nbr3x3;

    ss.clear();
    pt.clear();

    ss << world_state.observations.at(0).get()->text;
    boost::property_tree::read_json(ss, pt);
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, pt.get_child("nbr3x3"))
    {
        assert(v.first.empty());
        nbr3x3.push_back(v.second.data());
    }

    return nbr3x3;
}
    void calcNbrIndex();
        int front_of_me_idx = 0;
        int front_of_me_idxr = 0;
        int front_of_me_idxl = 0;        
        int right_of_me_idx = 0;
        int left_of_me_idx = 0; 
        
        int yaw = 0;
int main(int argc, const char **argv)
{
        int y = 0;
        int  z = 0;
        int pitch = 0;
        int fel = 0;
        int virag = 0;

        bool GOING_UP = true;
        bool FIRST_TURN = false;
        bool FORWARD = false;
        bool TURNING = false;
        bool FLOWER = false;
        bool ATTACK = false;
        bool PICK_UP = false;
        bool LVL_DOWN = false;
        bool ELSO=false;
        bool flower2=false;
    
        int trapc = 0;
        int lvl = 0;
        int lvlc = 0;
        
    AgentHost agent_host;

    try
    {
        agent_host.parseArgs(argc, argv);
    }
    catch( const exception& e )
    {
        cout << "ERROR: " << e.what() << endl;
        cout << agent_host.getUsage() << endl;
        return EXIT_SUCCESS;
    }
    if( agent_host.receivedArgument("help") )
    {
        cout << agent_host.getUsage() << endl;
        return EXIT_SUCCESS;
    }

    std::ifstream xmlf("nb4tf4i_d.xml");
    std::string xml {std::istreambuf_iterator<char>(xmlf),std::istreambuf_iterator<char>()};

    MissionSpec my_mission {xml,true};

    MissionRecordSpec my_mission_record("./saved_data.tgz");

    int attempts = 0;
    bool connected = false;
    do {
        try {
            agent_host.startMission(my_mission, my_mission_record);
            connected = true;
        }
        catch (exception& e) {
            cout << "Error starting mission: " << e.what() << endl;
            attempts += 1;
            if (attempts >= 3)
                return EXIT_FAILURE;    // Give up after three attempts.
            else
                boost::this_thread::sleep(boost::posix_time::milliseconds(1000));   // Wait a second and try again.
        }
    } while (!connected);

    WorldState world_state;

    cout << "Waiting for the mission to start" << flush;
    do {
        cout << "." << flush;
        boost::this_thread::sleep(boost::posix_time::milliseconds(100));
        world_state = agent_host.getWorldState();
        for( boost::shared_ptr<TimestampedString> error : world_state.errors )
            cout << "Error: " << error->text << endl;
    } while (!world_state.has_mission_begun);
    cout << endl;

    world_state = agent_host.getWorldState();

    agent_host.sendCommand("look 1");
    agent_host.sendCommand("look 1");

    do {

        if(world_state.number_of_observations_since_last_state != 0)
        {
            std::stringstream ss;
            ss << world_state.observations.at(0).get()->text;
            boost::property_tree::ptree pt;
            boost::property_tree::read_json(ss, pt);

            vector<std::string> nbr3x3;

            nbr3x3 = GetItems(world_state,ss,pt);
            for(vector< boost::shared_ptr< TimestampedString>>::iterator it = world_state.observations.begin();it !=world_state.observations.end();++it)
            {
            boost::property_tree::ptree pt;
            istringstream iss((*it)->text);
            boost::property_tree::read_json(iss, pt);

            string x =pt.get<string>("LineOfSight.type");	
            string LookingAt =pt.get<string>("XPos");
            y = pt.get<double>("YPos");
            yaw = pt.get<double>("Yaw");
            cout<<" Steve's Coords: "<<x<<" "<<y<<" "<<yaw<<" "<<"RF:"<<virag;
            }
            calcNbrIndex();
            if (GOING_UP==true){
                if (fel<30 && FORWARD==false){
                        agent_host.sendCommand("move 1");
                        agent_host.sendCommand("jumpmove 1");
                        fel++;
                        cout<<"MEGYEK FEL,"<<fel;
                }
                if(fel==30 && ELSO==false){
                    agent_host.sendCommand( "turn 1" );
                    FIRST_TURN=true;
                }
            if (FIRST_TURN==true){
            cout<<"\nELSO FORDULAS";
            if (nbr3x3[left_of_me_idx+9] == "air" && nbr3x3[front_of_me_idx+9] == "air" && nbr3x3[right_of_me_idx+9]=="air")
            {
                agent_host.sendCommand( "strafe -1" );
                boost::this_thread::sleep(boost::posix_time::milliseconds(50));
                cout<<"\nFALHOZ HUZODOM : ";
            }
            FIRST_TURN=false;
            FORWARD=true;
            ELSO=true;
            }
            if (FORWARD==true){

            cout<<"\nELŐRE MEGYEK";

            if (nbr3x3[9]=="dirt" && nbr3x3[10]=="dirt" && nbr3x3[11]=="dirt" && nbr3x3[12]=="dirt" && nbr3x3[14]=="dirt" && nbr3x3[15]=="dirt" && nbr3x3[16]=="dirt" && nbr3x3[17]=="dirt")
            {
                cout<<"\nEGYENESEN CSAPDA";
                agent_host.sendCommand( "jumpmove 1" );
                boost::this_thread::sleep(boost::posix_time::milliseconds(25));
            }
            if (nbr3x3[front_of_me_idx+9] == "air" && nbr3x3[front_of_me_idx] == "dirt")
            {
                agent_host.sendCommand( "move 1" );
                boost::this_thread::sleep(boost::posix_time::milliseconds(50));
                cout<<"\nELŐRE MEGYEK move1 : "<<nbr3x3[10];
            }
            else if (nbr3x3[front_of_me_idx+9]=="dirt")
            {
                cout<<"\nFORDULOK";
                agent_host.sendCommand( "turn 1" );
                boost::this_thread::sleep(boost::posix_time::milliseconds(25));
                TURNING=true;
                FORWARD=false;
            }
            else if (nbr3x3[front_of_me_idx+9] == "red_flower")
            {
                cout<<"\nELŐTTEM VAN EGY VIRÁG";
                FLOWER=true;
                FORWARD=false;
            }
            else if (nbr3x3[4+9] == "red_flower") 
            {
                cout<<"\nALATTAM VAN EGY VIRAG";
                FLOWER=true;
                FORWARD=false;
            }
            else
            {
                cout<<" Hoppá ";
                break;
            }
        }
            
        if (TURNING==true){     
            
            cout<<"\nFORDULAS";
            if (nbr3x3[front_of_me_idx+9] == "air")
            {
                TURNING=false;
                FORWARD=true;
                cout<<"\nELORE KELL MENNI";
            }
            if (nbr3x3[9]=="dirt" && nbr3x3[10]=="dirt" && nbr3x3[11]=="dirt" && nbr3x3[12]=="dirt" && nbr3x3[14]=="dirt" && nbr3x3[15]=="dirt" && nbr3x3[16]=="dirt" && nbr3x3[17]=="dirt")
            {
                cout<<"\nCSAPDA";
                agent_host.sendCommand( "jumpmove 1" );
                boost::this_thread::sleep(boost::posix_time::milliseconds(100));
            }
            if (nbr3x3[front_of_me_idx+9] == "red_flower")
            {     
                cout<<"\nTAMADASRA FELKESZULNI";
                agent_host.sendCommand( "move 1" );
                boost::this_thread::sleep(boost::posix_time::milliseconds(200));
                FLOWER=true;
                TURNING=false;
            }
            
        }
        if (FLOWER==true)
        {                        
            agent_host.sendCommand( "attack 1" );
            lvl = y;
            boost::this_thread::sleep(boost::posix_time::milliseconds(700));
            PICK_UP=true;
            FLOWER=false;
        }
        if (PICK_UP==true)
        {            
            cout<<"\nFELVESZEM";

            if (nbr3x3[front_of_me_idx+9] == "red_flower")
            {
                cout<<"\nFELSZEDOS TAMADAS";
                agent_host.sendCommand( "jump 1" );
                //agent_host.sendCommand( "attack 1" );
                flower2=true;
            }
            
            if (nbr3x3[9]=="dirt" && nbr3x3[10]=="dirt" && nbr3x3[11]=="dirt" && nbr3x3[12]=="dirt" && nbr3x3[14]=="dirt" && nbr3x3[15]=="dirt" && nbr3x3[16]=="dirt" && nbr3x3[17]=="dirt")
            {
                cout<<"\nFELSZEDOS CSAPDA";
                if (trapc < 1)
                {
                    cout<<"\nPICK_UP: trap if";
                    agent_host.sendCommand( "jumpmove -1" );
                    agent_host.sendCommand( "jumpmove -1" );
                    trapc = trapc + 1;
                }
                else
                {    
                    cout<<"\nPICK_UP: trap else";
                    agent_host.sendCommand( "jumpmove 1" );
                    agent_host.sendCommand( "jumpmove 1" );
                    trapc = 0;
                }
            }
            else
                trapc = 0;
            if (flower2==true)
            {
                virag++;
                cout<<"\nKISZEDVE";
                LVL_DOWN=true;
                flower2=false;
                PICK_UP=false;
            }
            else
            {
                agent_host.sendCommand( "move 1" );
                cout<<"   PICK_UP: WHAT CAN WE DO? ";
            }

        }
        if (LVL_DOWN==true){            
            cout<<"\nLVL_DOWN";

            if (nbr3x3[9]=="dirt" && nbr3x3[10]=="dirt" && nbr3x3[11]=="dirt" && nbr3x3[12]=="dirt" && nbr3x3[14]=="dirt" && nbr3x3[15]=="dirt" && nbr3x3[16]=="dirt" && nbr3x3[17]=="dirt")
            {   cout<<"   LVL_DOWN: trap ";
                if (nbr3x3[front_of_me_idx+18] == "dirt" and nbr3x3[left_of_me_idx+18] == "dirt")
                {
                    cout<<"      LVL_DOWN: trap elotte 2x dirt";
                    agent_host.sendCommand( "turn 1" );
                }
                agent_host.sendCommand( "jumpmove 1" );
                boost::this_thread::sleep(boost::posix_time::milliseconds(75));
                    
            }
            else
            {

                if (lvl != y + 1 )
                {    
                    cout<<"\nLVL_DOWN: turn move turn ";
                    if (lvlc < 2)
                    {
                        cout<<"\nLVL_DOWN: lvlc if";
                        agent_host.sendCommand( "move 1" );
                        agent_host.sendCommand( "move 1" );
                        agent_host.sendCommand( "strafe 1" );
                        agent_host.sendCommand( "strafe 1" );
                        boost::this_thread::sleep(boost::posix_time::milliseconds(300));
                        lvlc = lvlc + 1;
                    }
                    else
                    {   
                        cout<<"\nLVL_DOWN: lvlc else";
                        agent_host.sendCommand( "move -1" );
                        agent_host.sendCommand( "move -1" );
                        agent_host.sendCommand( "strafe 1" );
                        agent_host.sendCommand( "strafe 1" );
                        boost::this_thread::sleep(boost::posix_time::milliseconds(300));
                        lvlc = 0;
                    }  
                }
                else
                {
                    lvlc = 0;
                    cout<<"   LVL_DOWN: not trap ";
                    FORWARD=true;
                    LVL_DOWN=false;
                }
            }
       }
        
    }
}        
        world_state = agent_host.getWorldState();
    } while (world_state.is_mission_running);

    cout << "Mission has stopped." << endl;

    return EXIT_SUCCESS;
}

void calcNbrIndex(){
        if (yaw >= 180-22.5 and yaw <= 180+22.5)
        {
            front_of_me_idx = 1;
            front_of_me_idxr = 2;
            front_of_me_idxl = 0;
            right_of_me_idx = 5;
            left_of_me_idx = 3; 
        }
        else if (yaw >= 180+22.5 and yaw <= 270-22.5)
        {
            front_of_me_idx = 2; 
            front_of_me_idxr = 5;
            front_of_me_idxl =1;             
            right_of_me_idx = 8;
            left_of_me_idx = 0;
        }            
        else if (yaw >= 270-22.5 and yaw <= 270+22.5) 
        {
            front_of_me_idx = 5;
            front_of_me_idxr = 8;
            front_of_me_idxl = 2;
            right_of_me_idx = 7;
            left_of_me_idx = 1;   
        }
        else if (yaw >= 270+22.5 and yaw <= 360-22.5)
        {
            front_of_me_idx = 8;            
            front_of_me_idxr = 7;
            front_of_me_idxl = 5;          
            right_of_me_idx = 6;
            left_of_me_idx = 2;    
        }
        else if (yaw >= 360-22.5 or yaw <= 0+22.5)
        {
            front_of_me_idx = 7;
            front_of_me_idxr = 6;
            front_of_me_idxl = 8;
            right_of_me_idx = 3;
            left_of_me_idx = 5;     
        }
        else if (yaw >= 0+22.5 and yaw <= 90-22.5) 
        {
            front_of_me_idx = 6;
            front_of_me_idxr = 3;
            front_of_me_idxl = 7;         
            right_of_me_idx = 0;
            left_of_me_idx = 8;   
        }
        else if (yaw >= 90-22.5 and yaw <= 90+22.5) 
        {
            front_of_me_idx = 3;
            front_of_me_idxr = 0;
            front_of_me_idxl = 6;
            right_of_me_idx = 1;
            left_of_me_idx = 7;    
        }
        else if (yaw >= 90+22.5 and yaw <= 180-22.5)
        {
            front_of_me_idx = 0;
            front_of_me_idxr = 1;
            front_of_me_idxl = 3;
            right_of_me_idx = 2;
            left_of_me_idx = 6;  
        }
        else
            cout<<"There is great disturbance in the Force...";
    }
