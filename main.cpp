#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <stack>
#include <list>
#include <iomanip>
#include<cctype>
#include <iterator>
#include <sstream>
#include <forward_list>
#include <cmath>


using namespace std;

string name;
int x_axis;
int y_axis;

//i just create a structure for the node, with the name, the x, y axis and the neighbor vector 
struct node{

string name;
int x_axis;
int y_axis;
bool visited;
float distance=0.00;
float rist_dist=0.00;
int city=1;
int output_city=1;
vector<node> neighbor;
vector<node> cities;
vector<node> prev_cities;


};

//lines vector just fills up with the points that i grabat the location txt 
vector<node> lines;
vector<node> visited;
vector<node> visited1;
vector<node> visited2;
vector<node> visited3;
//vector<node> path;
vector<node>excluded;
vector<node> count_cities;



//i create a helper function that will return the index of the string i need, for when i update the neighbors i need to know where in my ines vector
// is this string(A1) located
int find_name(string name,vector<node> lines){
  int x;
for(int i=0; i<lines.size();i++){
 
    if(lines[i].name==name){
     x=i;   
    }

}
return x;

};

bool PersonComparer(const node& p1, const node& p2)
{
  // sort by name
  return p1.name < p2.name;
  //sort by age 
  //return p1.age < p2.age;
}
bool Comparator(const node& p1, const node& p2)
{
  // sort by name
  return p1.rist_dist < p2.rist_dist;
  //sort by age 
  //return p1.age < p2.age;
}
bool City(const node& p1, const node& p2)
{
  // sort by name
  return p1.city < p2.city ;
  //sort by age 
  //return p1.age < p2.age;
}

bool explored(node temp, vector<node> vec){

        for(int i=0;i<vec.size();i++){
            
            if(temp.name == vec[i].name){
                return true;
            }
        }
    return false;

};

bool find(node name, vector<node> vec){
       
        for(int i=0; i< vec.size(); i++){
            
            if(name.name == vec[i].name){
                return true;
            }
        }

        return false;

};

int count(node x, node y){

    int count=0;
    
    if(explored(x,count_cities) ==false && explored(y,count_cities)==false){
         count_cities.push_back(x);
         count_cities.push_back(y);
            count +=2;  
       }
    else if(explored(x, count_cities)==true && explored(y,count_cities)==false){
       count_cities.push_back(y);
        count +=1;
    }
   
return count;
};
double get_distance(int x, int y , int x1, int y1){
    double z =pow((x1-x), 2);
    double z1= pow((y1-y),2);
    return sqrt(z1+z);

}

bool DFS(node start,node end, vector<node> vec,vector<node> prev,vector<node> &path){
    
    vector<node>previous;

            int x;
            x=find_name(start.name,lines);
            start.name=lines[x].name;
            start.x_axis=lines[x].x_axis;
            start.y_axis=lines[x].y_axis;
      
            for(int i=0; i<lines[x].neighbor.size();i++){
                //if(explored(lines[x].neighbor[i],visited) == false){

                start.neighbor.push_back(lines[x].neighbor[i]);
                start.neighbor=lines[x].neighbor;
               // }
            }

            vector<node> :: iterator it;
            for(it=start.neighbor.begin(); it<start.neighbor.end();it++){
               
                for(int j=0; j<vec.size();j++){
                    
                    if(it->name == vec[j].name){
                      it= start.neighbor.erase(it);
                      --it;
                         break;
                }

            }
            }
            visited.push_back(start);
            path.push_back(start);
            cout<<endl;
           

            for(int i=0; i < start.neighbor.size();i++){
                
                if(start.neighbor[i].distance == 0){
                
                float dis= get_distance(start.x_axis, start.y_axis, start.neighbor[i].x_axis, start.neighbor[i].y_axis);
                
                start.neighbor[i].distance = dis + start.distance;
                //cout<<dis<<endl;
                int dis2=get_distance(start.neighbor[i].x_axis, start.neighbor[i].y_axis, end.x_axis, end.y_axis);
                
                start.neighbor[i].rist_dist = dis2 + start.neighbor[i].distance;

                start.neighbor[i].prev_cities.push_back(start);

                for(int j=0; j<start.prev_cities.size();j++){
                    start.neighbor[i].prev_cities.push_back(start.prev_cities[j]);
                }
               
            
                }
                else if(start.neighbor[i].distance != 0){
                   // cout<<start.neighbor[i].name <<"("<<start.neighbor[i].distance<<")"<<" ";
                   // dist.push_back(start.neighbor[i].distance);
                    continue;

                }
                
                }  
                    if(start.name==end.name){
                         return true;
                           }
             cout <<"City Selected: " <<start.name<<endl;
            cout<<"Possible cities to where to travel: ";
           
            for(int i=0; i< start.neighbor.size();i++){
                 cout<<start.neighbor[i].name<<" ";
                }
                cout<<endl;

            cout<<"Cities at the end of possible paths: ";
              
                    vector<node> ::iterator it2;
                    vector<node> ::iterator it3;
                    
                    for(it2=start.neighbor.begin(); it2<start.neighbor.end();it2++){
                           
                            for(it3=prev.begin();it3<prev.end();it3++){
                                if(it2->name == it3->name){
                                    if(it2->distance <= it3->distance){
                                        it3=prev.erase(it3);
                                        --it3;
                                        break;
                                        
                                    }
                                    else{
                                        it2=start.neighbor.erase(it2);
                                        --it2;
                                        break;
                                        
                                    }
                                }
                            }
                        }
                

                    for(int i=0; i<start.neighbor.size();i++){
                        
                        if(find(start.neighbor[i], visited)==true){
                                start.neighbor.erase(start.neighbor.begin() + i);
                                --i;
                                continue;
                        }

                    }
                   
                    for(int i=0; i<prev.size();i++){
                        start.neighbor.push_back(prev[i]);
                        
                    }


                    for(int i=0;i<start.neighbor.size();i++){
                        cout<<start.neighbor[i].name<<"("<<start.neighbor[i].distance<<")"<<" ";
                    }

                        cout<<"\n";
                

                    for(int i=0; i<start.neighbor.size();i++){
                        sort(start.neighbor.begin(),start.neighbor.end(),Comparator);
                        //cout<<start.neighbor[i].name<<endl;
                    }


                for(int i=1; i<start.neighbor.size();i++){
                        
                        previous.push_back(start.neighbor[i]);
                
                }
                
                for(int i=0; i<start.neighbor.size();i++){
                   
                    if(explored(start.neighbor[i],visited) == false ){

                  if(DFS(start.neighbor[i], end,vec,previous,path)){
                      
                        return true;
                    }
                    }
                }
            //else continue;
        

       

   return false; 
}; 
bool DFS_OUT(node start,node end, vector<node> vec,vector<node> prev,vector<node> &path){
    
    vector<node>previous;
            int x;
            x=find_name(start.name,lines); start.name=lines[x].name;
            start.x_axis=lines[x].x_axis;start.y_axis=lines[x].y_axis;
      
            for(int i=0; i<lines[x].neighbor.size();i++){
                start.neighbor.push_back(lines[x].neighbor[i]);
                start.neighbor=lines[x].neighbor;}
            vector<node> :: iterator it;
            for(it=start.neighbor.begin(); it<start.neighbor.end();it++){
                    for(int j=0; j<vec.size();j++){
                        if(it->name == vec[j].name){
                            it= start.neighbor.erase(it); --it;
                            break; }}}
            visited1.push_back(start);
            path.push_back(start);
           // cout<<endl;
            for(int i=0; i < start.neighbor.size();i++){ 
                if(start.neighbor[i].distance == 0){
            float dis= get_distance(start.x_axis, start.y_axis, start.neighbor[i].x_axis, start.neighbor[i].y_axis);
            start.neighbor[i].distance = dis + start.distance;
            int dis2=get_distance(start.neighbor[i].x_axis, start.neighbor[i].y_axis, end.x_axis, end.y_axis);
            start.neighbor[i].rist_dist = dis2 + start.neighbor[i].distance;
            start.neighbor[i].prev_cities.push_back(start);
                for(int j=0; j<start.prev_cities.size();j++){
                    start.neighbor[i].prev_cities.push_back(start.prev_cities[j]);
                } }
                else if(start.neighbor[i].distance != 0){
                    continue; } }  
                    if(start.name==end.name){
                         return true;
                           }
                    vector<node> ::iterator it2;
                    vector<node> ::iterator it3;
                    
                    for(it2=start.neighbor.begin(); it2<start.neighbor.end();it2++){
                           
                            for(it3=prev.begin();it3<prev.end();it3++){
                                if(it2->name == it3->name){
                                    if(it2->distance <= it3->distance){
                                        it3=prev.erase(it3);
                                        --it3;
                                        break;      
                                    }
                                    else{
                                        it2=start.neighbor.erase(it2);
                                        --it2;
                                        break;
                                        
                                    }
                                }
                            }
                        }
                

                    for(int i=0; i<start.neighbor.size();i++){
                        
                        if(find(start.neighbor[i], visited1)==true){
                                start.neighbor.erase(start.neighbor.begin() + i);
                                --i;
                                continue;
                        }

                    }
                    for(int i=0; i<prev.size();i++){
                        start.neighbor.push_back(prev[i]);
                        
                    }
                    for(int i=0; i<start.neighbor.size();i++){
                        sort(start.neighbor.begin(),start.neighbor.end(),Comparator);
                        //cout<<start.neighbor[i].name<<endl;
                    }
                     for(int i=1; i<start.neighbor.size();i++){
                        
                        previous.push_back(start.neighbor[i]);
                
                    }
                
                for(int i=0; i<start.neighbor.size();i++){
                   
                    if(explored(start.neighbor[i],visited1) == false ){

                  if(DFS_OUT(start.neighbor[i], end,vec,previous,path)){
                      
                        return true;
                    }
                    }
                }
   return false; 
}; 
bool cities(node start,node end, vector<node> vec,vector<node> prev,vector<node> &path){
    
        vector<node>previous;
        int x;
        x=find_name(start.name,lines);
        start.name=lines[x].name;start.x_axis=lines[x].x_axis;start.y_axis=lines[x].y_axis;
    
            for(int i=0; i<lines[x].neighbor.size();i++){
                start.neighbor.push_back(lines[x].neighbor[i]);
                start.neighbor=lines[x].neighbor;
            }
              vector<node> :: iterator it;
            for(it=start.neighbor.begin(); it<start.neighbor.end();it++){
               
                for(int j=0; j<vec.size();j++){
                    
                    if(it->name == vec[j].name){
                      it= start.neighbor.erase(it);
                      --it;
                         break;
                }

            }
            }          
            visited2.push_back(start);
            path.push_back(start);
            cout<<endl;
            for(int i=0; i < start.neighbor.size();i++){
               
                start.neighbor[i].city= start.neighbor[i].city + start.city;
                start.neighbor[i].cities.push_back(start);

                for(int j=0; j<start.cities.size();j++){
                    start.neighbor[i].cities.push_back(start.cities[j]);
                }     
                }  
                 
                 if(start.name==end.name){
                            //start.cities.push_back(end);
                             return true;
                          }
                
                 cout <<"City Selected: " <<start.name<<endl;
                 cout<<"Possible cities to where to travel: ";
           
                for(int i=0; i< start.neighbor.size();i++){
                 cout<<start.neighbor[i].name<<" ";
                }
                cout<<endl;

                cout<<"Cities at the end of possible paths: ";
              
                    vector<node> ::iterator it2;
                    vector<node> ::iterator it3;
                    
                for(it2=start.neighbor.begin(); it2<start.neighbor.end();it2++){
                    for(it3=prev.begin();it3<prev.end();it3++){
                        if(it2->name == it3->name){
                            if(it2->city <= it3->city){
                                it3=prev.erase(it3);
                                 --it3;
                                 break;
                                    }
                            else{
                                it2=start.neighbor.erase(it2);
                                --it2;
                                break;
                                    }
                                }
                            }
                        }
                    for(int i=0; i<start.neighbor.size();i++){
                       if(find(start.neighbor[i], visited2)==true){
                                start.neighbor.erase(start.neighbor.begin() + i);
                                --i;
                                continue;
                        }
                    }
                   
                    for(int i=0; i<prev.size();i++){
                        start.neighbor.push_back(prev[i]);    
                    }
                    for(int i=0;i<start.neighbor.size();i++){
                        cout<<start.neighbor[i].name<<"("<<start.neighbor[i].output_city<<")"<<" ";
                    }  cout<<"\n";
                    //vector<node >:: iterator temp;
                    //temp=start.neighbor.begin();
                    for(int i=0; i<start.neighbor.size();i++){
                        sort(start.neighbor.begin(),start.neighbor.end(),City);
                       
                    }
                
                for(int i=1; i<start.neighbor.size();i++){
                      previous.push_back(start.neighbor[i]);
                     }
                for(int i=0; i<start.neighbor.size();i++){
                   if(start.neighbor[i].name == end.name){

                   }
                    if(explored(start.neighbor[i],visited2) == false ){

                    if(cities(start.neighbor[i], end,vec,previous,path)){
                      
                        return true;
                    }
                    }
                }
   return false; 
}; 
bool cities_output(node start,node end, vector<node> vec,vector<node> prev,vector<node> &path){
    
        vector<node>previous;
        int x;
        x=find_name(start.name,lines);
        start.name=lines[x].name;start.x_axis=lines[x].x_axis;start.y_axis=lines[x].y_axis;
    
            for(int i=0; i<lines[x].neighbor.size();i++){
                start.neighbor.push_back(lines[x].neighbor[i]);
                start.neighbor=lines[x].neighbor;
            }
              vector<node> :: iterator it;
            for(it=start.neighbor.begin(); it<start.neighbor.end();it++){
               
                for(int j=0; j<vec.size();j++){
                    
                    if(it->name == vec[j].name){
                      it= start.neighbor.erase(it);
                      --it;
                         break;
                }

            }
            }          
            visited3.push_back(start);
            path.push_back(start);
           // cout<<endl;
            for(int i=0; i < start.neighbor.size();i++){
               
                start.neighbor[i].city= start.neighbor[i].city + start.city;
                start.neighbor[i].cities.push_back(start);

                for(int j=0; j<start.cities.size();j++){
                    start.neighbor[i].cities.push_back(start.cities[j]);
                }     
                }  
                 if(start.name==end.name){
                            //start.cities.push_back(end);
                             return true;
                          }
                    vector<node> ::iterator it2;
                    vector<node> ::iterator it3;
                    
                for(it2=start.neighbor.begin(); it2<start.neighbor.end();it2++){
                    for(it3=prev.begin();it3<prev.end();it3++){
                        if(it2->name == it3->name){
                            if(it2->city <= it3->city){
                                it3=prev.erase(it3);
                                 --it3;
                                 break;
                                    }
                            else{
                                it2=start.neighbor.erase(it2);
                                --it2;
                                break;
                                    }
                                }
                            }
                        }
                    for(int i=0; i<start.neighbor.size();i++){
                       if(find(start.neighbor[i], visited3)==true){
                                start.neighbor.erase(start.neighbor.begin() + i);
                                --i;
                                continue;
                        }
                    }
                   
                    for(int i=0; i<prev.size();i++){
                        start.neighbor.push_back(prev[i]);    
                    }
                    
                    for(int i=0; i<start.neighbor.size();i++){
                        sort(start.neighbor.begin(),start.neighbor.end(),City);
                    }
                    for(int i=1; i<start.neighbor.size();i++){
                      previous.push_back(start.neighbor[i]);
                     }
                    for(int i=0; i<start.neighbor.size();i++){
                   
                    if(explored(start.neighbor[i],visited3) == false ){

                    if(cities_output(start.neighbor[i], end,vec,previous,path)){
                      
                        return true;
                    }
                    }
                }
   return false; 
}; 


int main(){
    string line;
    int number_of_lines=0;
    
    node n;
    string line2;
    ifstream locations;
    ifstream connections;
    
    //open the location file to get the lines
    locations.open("locations.txt");
    //connections.open("connections.txt");

    if(locations.is_open()){
        while(!locations.eof()){
            //i just iterate through the lines and put the objects in a structure vector 
            getline(locations,line);
            stringstream ss(line);
            //cout<< line << endl;

            if(line=="END"){
                break;
            }

            ss>>name>>x_axis>>y_axis;
            
            n.name=name;
           
            n.x_axis=x_axis;
            n.y_axis=y_axis;
            //as i read the lines put them in a vector call lines
            lines.push_back(n);
            
            ss.clear();
            ++number_of_lines;
        }
        locations.close();
    }
    //open the connections file to reade the lines and grab teh neighbors of teh string
    connections.open("connections.txt");
    
    int index;
    int index2;
    string name0;
    int number;
    string name1;
    string name2;
    string name3;
    string name4;
    string name5;
    string name6;

//check this part, i want to say that if the integer next to thename is 1 it means that it has 1 neighbor, so find it in the lines vector and push back into 
//the neighbor vector of that string and so on, with possibiltie of the string been 2,3,4,5.
    if(connections.is_open()){
        while(!connections.eof()){
            
            getline(connections,line2);
            stringstream ss1(line2);
            //cout<<line2<<endl;

            if(line2=="END"){
                break;
           }
           
           ss1>>name0>>number>>name1>>name2>>name3>>name4;
         
              if(number== 1 ){
                ss1>>name0>>number>>name1;

                //cout<<name0<<number<<name1;
               
               index=find_name(name1,lines);
               index2=find_name(name0,lines);
               lines[index2].neighbor.push_back(lines[index]);
               
           }
          else if(number == 2 ){
               ss1>>name0>>number>>name1>>name2;

               index=find_name(name0,lines);
               int index1=find_name(name1,lines);
               int index2=find_name(name2,lines);
               lines[index].neighbor.push_back(lines[index1]);
               lines[index].neighbor.push_back(lines[index2]); 
          
           }
          else if(number==3 ){
               ss1>>name0>>number>>name1>>name2>>name3;
               //cout<<name0<<number<<name1<<name2<<name3;
               index= find_name(name0,lines);
               int index1=find_name(name1,lines);
               int index2=find_name(name2, lines);
               int index3=find_name(name3, lines);
               lines[index].neighbor.push_back(lines[index1]);
               lines[index].neighbor.push_back(lines[index2]);
               lines[index].neighbor.push_back(lines[index3]);
               
           }
           else if(number==4 ){
               ss1>>name0>>number>>name1>>name2>>name3>>name4;
               index=find_name(name0,lines);
               int index1=find_name(name1,lines);
               int index2=find_name(name2,lines);
               int index3=find_name(name3,lines);
               int index4=find_name(name4, lines);
               lines[index].neighbor.push_back(lines[index1]);
               lines[index].neighbor.push_back(lines[index2]);
               lines[index].neighbor.push_back(lines[index3]);
               lines[index].neighbor.push_back(lines[index4]);

           }
           else if(number==5 ){
               ss1>>name0>>number>>name1>>name2>>name3>>name4;
               index=find_name(name0,lines);
               int index1=find_name(name1,lines);
               int index2=find_name(name2,lines);
               int index3=find_name(name3,lines);
               int index4=find_name(name4, lines);
               int index5=find_name(name5,lines);
               lines[index].neighbor.push_back(lines[index1]);
               lines[index].neighbor.push_back(lines[index2]);
               lines[index].neighbor.push_back(lines[index3]);
               lines[index].neighbor.push_back(lines[index4]);
                lines[index].neighbor.push_back(lines[index5]); 
                //lines[index].neighbor.front();
           }
          else if(number==6 ){
              ss1>>name0>>number>>name1>>name2>>name3>>name4>>name5>>name6;
               index=find_name(name0,lines);
               int index1=find_name(name1,lines);
               int index2=find_name(name2,lines);
               int index3=find_name(name3,lines);
               int index4=find_name(name4, lines);
               int index5=find_name(name5,lines);
               int index6=find_name(name6, lines);
               lines[index].neighbor.push_back(lines[index1]);
               lines[index].neighbor.push_back(lines[index2]);
               lines[index].neighbor.push_back(lines[index3]);
               lines[index].neighbor.push_back(lines[index4]);
                lines[index].neighbor.push_back(lines[index5]);  
                lines[index].neighbor.push_back(lines[index6]); 
                
           }
          }
          connections.close();       
        }

        for(int i=0; i<lines.size();i++){
            //cout << "inside first:: "<<lines[i].name<<" "<<lines[i].x_axis<<" "<<lines[i].y_axis<< endl;
          
          for(int j=0; j<lines[i].neighbor.size();j++){
             sort(lines[i].neighbor.begin(),lines[i].neighbor.end(), PersonComparer); 
          }
        }         
    string start;
    string end;
    string command;
    string line3;
    string a,b,c,d,e,f,g,h,i;
    ifstream exclude;

    while(command != "x" || command != "exit"){
    
    cout<<"-------------------------------------"<<endl;
    
    cout<<"Enter starting point: ";
    getline(cin,start);
    if(start== "x" || start=="exit"){
        break;
    }
    cout<<"Entert the goal point: ";
    getline(cin,end);
   if(end== "x" || end=="exit"){
        break;
    } 
    cout<<"Enter cities to exclude (More than 1 city,seperate by space): ";
    getline(cin,line3,'\n');
    if(line3== "x" || line3=="exit"){
        break;
    }

    stringstream ss(line3);

      ss>>a>>b>>c>>d>>e>>f>>g>>h>>i;
      int index =find_name(a,lines);
      int index1=find_name(b,lines);
      int index2=find_name(c,lines);
      int index3=find_name(d,lines);
      int index4=find_name(e,lines);
      int index5=find_name(f,lines);
      int index6=find_name(g,lines);
      int index7=find_name(h,lines);
      int index8=find_name(i,lines);

      excluded.push_back(lines[index]);
      excluded.push_back(lines[index1]);
      excluded.push_back(lines[index2]);
      excluded.push_back(lines[index3]);
      excluded.push_back(lines[index4]);
      excluded.push_back(lines[index5]);
      excluded.push_back(lines[index6]);
      excluded.push_back(lines[index7]);
      excluded.push_back(lines[index8]);
   
    node s;
    node e;
    int op1;
            s.name=start;
            op1=find_name(end,lines);
            e.name=lines[op1].name;
            e.x_axis=lines[op1].x_axis;
            e.y_axis=lines[op1].y_axis;
      

            for(int i=0; i<lines[op1].neighbor.size();i++){
                //if(explored(lines[x].neighbor[i],visited) == false){

                e.neighbor.push_back(lines[op1].neighbor[i]);
                e.neighbor=lines[op1].neighbor;
               // }
            } 
    string action;
    cout<<"Step by Step: yes or no? ";
    getline(cin,action);
    
    if(action=="y" ||action== "Y"|| action =="yes" ||action =="YES"){
    cout<<"Heuristic:"<<endl;
    cout<<"\t"<<"1-Straight Line Distance."<<endl;
    cout<<"\t"<<"2-Fewwest Cities."<<endl;
    cout<<"\t"<<"3-Exit."<<endl;
    cout<<"Command: ";
    getline(cin, command);
     
     
     
     if(command == "1"){
         
     vector<node>previous; vector<node> new_vec;
     cout<<"-------------------------------------"<<endl;
     vector<node>path;
     vector<node>path1;
        DFS(s,e,excluded,previous, path);
      
         vector<node> ::iterator back;
            back=path.end()-1;
            vector<node>::iterator it;

            it = back->prev_cities.begin();
            it = back->prev_cities.insert ( it , e );
            double total=0.0;
            cout<<"Output:"<<endl;
            for(int i=back->prev_cities.size()-1; i>0 ; --i){
                cout<<back->prev_cities[i].name<<" to " << back->prev_cities[i-1].name <<" length "<< get_distance(back->prev_cities[i].x_axis,back->prev_cities[i].y_axis, back->prev_cities[i-1].x_axis, back->prev_cities[i-1].y_axis)<<endl;
               total+=get_distance(back->prev_cities[i].x_axis,back->prev_cities[i].y_axis, back->prev_cities[i-1].x_axis, back->prev_cities[i-1].y_axis); 
                 
            }
            
            cout<< "Total path length: "<<total<<endl;
            cout<<"\n";
        break;
        }
        else if(command =="2"){
        vector<node>previous;
        vector<node>path;
        cities(s,e,excluded,previous,path);

            vector<node> ::iterator back;
            back=path.end()-1;
            vector<node>::iterator it;

            it = back->cities.begin();
            it = back->cities.insert ( it , e );
            int total=1;
            cout<<"Output:"<<endl;
            for(int i=back->cities.size()-1; i>0 ; --i){
                cout<<back->cities[i].name<<" to " << back->cities[i-1].name <<" length "<< count(back->cities[i], back->cities[i-1])<<endl;
                total+=1;
                 
            }
            
            cout<< "Total path length: "<<total<<endl;
            cout<<"\n";
        break;
        }
        else if(command =="3" || command== "exit" || command =="x" ||  command =="X"){
            break;
        }
        else 
        cout<<"Invalid command."<<endl;
        continue;
     
     }
     else if(action == "no" || action =="NO" ||action =="n"|| action== "N"){
        
        string op;
        cout<<"Heuristic: "<<endl;
        cout<<"\t"<<"1-Straight Distance."<<endl;
        cout<<"\t"<<"2-Fewest City."<<endl;
        cout<<"\t"<<"3-Exit."<<endl;
        cout<<"Command: ";
        getline(cin, op);
        
        
        if(op== "1"){
               
     vector<node>previous; //vector<node> new_vec;
     //cout<<"-------------------------------------"<<endl;
     //vector<node>path;
     vector<node>path1;
        DFS_OUT(s,e,excluded,previous, path1);
      
            vector<node> ::iterator back;
            back=path1.end()-1;
            vector<node>::iterator it;

            it = back->prev_cities.begin();
            it = back->prev_cities.insert ( it , e );
            double total=0.0;
            cout<<"Output:"<<endl;
            for(int i=back->prev_cities.size()-1; i>0 ; --i){
                cout<<back->prev_cities[i].name<<" to " << back->prev_cities[i-1].name <<" length "<< get_distance(back->prev_cities[i].x_axis,back->prev_cities[i].y_axis, back->prev_cities[i-1].x_axis, back->prev_cities[i-1].y_axis)<<endl;
               total+=get_distance(back->prev_cities[i].x_axis,back->prev_cities[i].y_axis, back->prev_cities[i-1].x_axis, back->prev_cities[i-1].y_axis); 
                 
            }
            
            cout<< "Total path length: "<<total<<endl;
            cout<<"\n";
        break; 
        }
        else if(op=="2"){

        vector<node>previous;
        vector<node>path2;
        cities_output(s,e,excluded,previous,path2);

            vector<node> ::iterator back;
            back=path2.end()-1;
            vector<node>::iterator it;

            it = back->cities.begin();
            it = back->cities.insert ( it , e );
            int total=1;
            cout<<"Output:"<<endl;
            for(int i=back->cities.size()-1; i>0 ; --i){
                cout<<back->cities[i].name<<" to " << back->cities[i-1].name <<" length "<< count(back->cities[i], back->cities[i-1])<<endl;
                total+=1;
                 
            }
            
            cout<< "Total path length: "<<total<<endl;
            cout<<"\n";
            break;
        }
        
        else if(op =="exit" || op =="x" || op=="3"){
            break;
        }
     }

    }
   

    return 0;
}