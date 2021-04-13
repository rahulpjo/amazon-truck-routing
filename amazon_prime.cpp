#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <cmath>
#include <algorithm>
#include <bits/stdc++.h> 

// 55.1
using namespace std;
class Address{
  //55.2.1  
  private:
    int date;
    int i;
    int j;
    bool prime;
  public:
    Address(){
      int date = 0;
      int x = 0;
      int y = 0;
    }
    Address(int i_coord, int j_coord){
      i = i_coord;
      j = j_coord;
    }
    Address(int deliv_date, int i_coord, int j_coord, bool p){
      date = deliv_date;
      i = i_coord;
      j = j_coord;
      prime = p;
    }
    
    bool operator==(Address b) {
         if ((this->getI() == b.getI())&&(this->getJ() == b.getJ())){
         	return true;
         }
         else{
         	return false;
         }
      }
    void operator=(Address b) {
         this->i = b.getI();
         this->j = b.getJ();
         this->prime = b.getPrime();
         return;
      }
    int getDate(){
      int d = date;
      return d;
    } 
    int getI(){
      int i_num = i;
      return i_num;
    }
    int getJ(){
      int j_num = j;
      return j_num;
    }
    bool getPrime(){
    	bool p = prime;
    	return p;
    }
    int distance(Address other){
      int dist = abs(i-other.getI()) + abs(j-other.getJ());
      return dist;
    }
    void addr_print(){
      cout << "(" << i << "," << j << ")";
      return;
    }
};

class AddressList{
  private:
    int size;
    int distance;
  public:
    vector<Address> addr_list;

    AddressList(Address x){
      this->addr_list.push_back(x);
    }
    
    AddressList(vector <Address> &x){
      addr_list.clear();
      for (int i = 0; i < x.size(); i++){
          this->addr_list.push_back(x[i]);
      }
      this->size = x.size();
      int total = 0;
      for (int i = 0; i < this->size-1; i++){
    	  total += addr_list[i].distance(addr_list[i+1]);
      }
      distance = total;
    }
     //55.2.1 Adds an address into the list
     void add_address(Address a) {
     	bool found = false;
    	for (int i = 0; i < size; i++){
    		if (a == addr_list[i]){
    			found = true;
    		}
    	}
    	if (~addr_list.empty()){
    		distance += (addr_list.back()).distance(a);
    	}
       if (!found){
             addr_list.push_back(a);
       }
       
     }
     void add_address(Address* a) {
     	bool found = false;
    	for (int i = 0; i < size; i++){
    		if (*a == addr_list[i]){
    			found = true;
    		}
    	}
    	distance += (addr_list.back()).distance(*a);
       if (!found){
             addr_list.push_back(*a);
       }
       
     }
    // //55.2.3: Finds closest delivery address (in list) to given address 
       int index_closest_to(Address a){
         Address not_found(0,0,0,0);
         Address temp;
         int min = INT_MAX;
         int curr = 0;
         int ind = 0;
         if (addr_list.empty()){
           return -1;
         }
         for (int i = 0; i < addr_list.size(); i++){
           curr = addr_list[i].distance(a);
           if(curr < min){
               min = curr;
               temp = addr_list[i];
               ind = i;
           }
         }
         return ind;
       }
       Address address_closest_to(Address a){
         Address not_found(0,0,0,0);
         Address temp;
         int min = INT_MAX;
         int curr = 0;
         if (addr_list.empty()){
           return not_found;
         }
         for (int i = 0; i < addr_list.size(); i++){
           curr = addr_list[i].distance(a);
           if(curr < min){
               min = curr;
               temp = addr_list[i];
           }
         }
         return temp;
       }
       
    void print_distance(){
    	cout << distance << endl;
    	return;
    }
    void print_path(){
    	addr_list[0].addr_print();
    	if (addr_list.size() == 1){
    		return;
    	}
    	for (int i = 1; i < addr_list.size(); i++){
    		cout << " --> ";
    		addr_list[i].addr_print();
    	}
    }
    //55.2.2: Returns the distance needed to travel to visit all addresses in order
    int get_distance() {
      return distance;
    }
    
};

// //We should start form (0,0) then move to our index_closest_of and then continually step through the list and keep calling i_c_of and doing that
 class Route: public AddressList {
 	public:
   		vector <Address> fin_path;
   		vector <Address> addr_path;
   		vector <Address> pathA;
   		vector <Address> pathB;
   		Address depot;
   		Route(vector <Address> &pathline)
   			:AddressList{pathline}{
         for(int i = 0; i < pathline.size(); i++){
           addr_path.push_back(pathline[i]);
         }
         Address depot(0,0,0,0);
         full_distance = get_distance() + addr_list[0].getI() + addr_list[0].getJ() + addr_list[addr_list.size()-1].getI() + addr_list[addr_list.size()-1].getJ();
    	}
  
   		void get_full_distance(){
        cout << full_distance << endl;
      } 
  		
   		void greedy_route(){
       //gonna try and implement a stack to do this
       		int total = 0;
       		deque<Address> s;
       		Address depot(0,0,0,0);
       		Address curr(1,0,0,0);
       		curr = address_closest_to(depot);
       		int addr_index = index_closest_to(depot);
       		while (!addr_list.empty()){
         		s.push_back(curr);
         		for(int i = 0; i < addr_list.size(); i++){
           			if (addr_list[i].getI() == curr.getI() && addr_list[i].getJ() == curr.getJ() ){
           				addr_list.erase(addr_list.begin()+i);
           			}
         		}
         		curr = address_closest_to(curr);
       		}
          addr_path.clear();
       		addr_path.push_back(depot);
       		while(!s.empty()){
       	  		addr_path.insert(addr_path.end(), s.at(0)); 
       	  		s.pop_front();
       		}
       		addr_path.insert(addr_path.end(), depot); 
       		cout << "Greedy Route Path: ";
       		for(int i = 0; i < addr_path.size(); i++){
           		addr_path[i].addr_print();
           		cout << " ";
         	}
         	cout << endl;
     	}
  
   // 55.4
   		void multi_trucks(int signal){
        //divide the total distance of the route by the number of trucks
       	Address mult_depot(0,0,0,0);
        if (signal == 1){
        	for (int i = 1; i < addr_path.size()-1; i++){
          		if (i%2==0){
            		pathA.push_back(addr_path[i]);
          		}
          		else {
            		pathB.push_back(addr_path[i]);
          		}
        	}
        	cout << "Splitting Path Between Two Trucks" << endl;
        }
        else if (signal == 2){
        	for (int i = 1; i < addr_path.size()-1; i++){
          		if (addr_path[i].getDate()==1){
            		pathA.push_back(addr_path[i]);
          		}
          		else {
            		pathB.push_back(addr_path[i]);
          		}
        	}
        	cout << "Splitting Path Between Two Days" << endl;
        }
        
        //Print our paths
        cout << "Path 1: ";
        mult_depot.addr_print();
        cout <<  "-->";
        for (int i = 0; i < pathA.size(); i++){
          if (i != pathA.size()-1){
            pathA[i].addr_print(); 
            cout << "-->";
          }
          else {
            pathA[i].addr_print(); 
            cout << "-->";
            mult_depot.addr_print();
            cout << endl;
          }
          
        }
        
        cout << "Path 2: ";
        mult_depot.addr_print();
        cout <<  "-->";
        for (int i = 0; i < pathB.size(); i++){
         if (i != pathB.size()-1){
            pathB[i].addr_print(); 
            cout << "-->";
          }
          else {
            pathB[i].addr_print();
            cout << "-->";
            mult_depot.addr_print();
            cout << endl;
          }
          
        }
      }
       
   		//55.4 (problem said we can assume that each truck gets a random list of addresses so no need for an algorithm to divide the paths that just happens with the user input)
         void two_paths(){//state assumption that both paths are the same length
           int it_x, it_y;
           Address mult_depot(0,0,0,0);
           int distA, distB, distA_rev, distB_rev; //values of current distances to next points and possible revised distances to next points
           for (it_x = 0; it_x < pathA.size(); it_x++){
             for (it_y = 0; it_y < pathB.size(); it_y++){
               distA = pathA[it_x].distance(pathA[it_x+1]); //distance from point to next point in one path
               distB = pathB[it_y].distance(pathB[it_y+1]); //distance from point to next point in another path
               distA_rev = pathA[it_x].distance(pathB[it_y+1]);//distance from point in one path to next point on the other path
               distB_rev = pathB[it_y].distance(pathA[it_x+1]);//vice versa
               if ((distA_rev < distA) && (distB_rev < distB)){ //if they're each closer to the other path's point then they switch 
                 Address temp = pathA[it_x]; //switch next point not current one bc switching current nodes would mean changing the 
                 pathA[it_x] = pathB[it_y];
                 pathB[it_y] = temp;       //distance between current points and the points before which we already tested to possibly not be optimal
               }
            }
           }
           //Print our paths
            cout << "Two Truck Optimization" << endl;
        	cout << "Path 1: ";
        	mult_depot.addr_print();
        	cout <<  "-->";
        	for (int i = 0; i < pathA.size(); i++){
          		if (i != pathA.size()-1){
            		pathA[i].addr_print(); 
            		cout << "-->";
          		}
          		else {
            		pathA[i].addr_print(); 
            		cout << "-->";
            		mult_depot.addr_print();
            		cout << endl;
          		}
          
        	}
        
        	cout << "Path 2: ";
        	mult_depot.addr_print();
        	cout <<  "-->";
        	for (int i = 0; i < pathB.size(); i++){
         		if (i != pathB.size()-1){
            		pathB[i].addr_print(); 
            		cout << "-->";
          		}
          		else {
            		pathB[i].addr_print();
            		cout << "-->";
            		mult_depot.addr_print();
            		cout << endl;
          		}
          
        	}
         }
         
         void two_paths_w_prime(){//state assumption that both paths are the same length
           int it_x, it_y;
           Address mult_depot(0,0,0,0);
           int distA, distB, distA_rev, distB_rev; //values of current distances to next points and possible revised distances to next points
           for (it_x = 0; it_x < pathA.size(); it_x++){
             for (it_y = 0; it_y < pathB.size(); it_y++){
               distA = pathA[it_x].distance(pathA[it_x+1]); //distance from point to next point in one path
               distB = pathB[it_y].distance(pathB[it_y+1]); //distance from point to next point in another path
               distA_rev = pathA[it_x].distance(pathB[it_y+1]);//distance from point in one path to next point on the other path
               distB_rev = pathB[it_y].distance(pathA[it_x+1]);//vice versa
               if ((distA_rev < distA) && (distB_rev < distB) && ~pathA[it_x].getPrime() && ~pathB[it_y].getPrime()){ //if they're each closer to the other path's point then they switch 
                 Address temp = pathA[it_x]; //switch next point not current one bc switching current nodes would mean changing the 
                 pathA[it_x] = pathB[it_y];
                 pathB[it_y] = temp;       //distance between current points and the points before which we already tested to possibly not be optimal
               }
            }
           }
           cout << "Two Truck Optimization with Prime" << endl;
           //Print our paths
        	cout << "Path 1: ";
        	mult_depot.addr_print();
        	cout <<  "-->";
        	for (int i = 0; i < pathA.size(); i++){
          		if (i != pathA.size()-1){
            		pathA[i].addr_print(); 
            		cout << "-->";
          		}
          		else {
            		pathA[i].addr_print(); 
            		cout << "-->";
            		mult_depot.addr_print();
            		cout << endl;
          		}
          
        	}
        
        	cout << "Path 2: ";
        	mult_depot.addr_print();
        	cout <<  "-->";
        	for (int i = 0; i < pathB.size(); i++){
         		if (i != pathB.size()-1){
            		pathB[i].addr_print(); 
            		cout << "-->";
          		}
          		else {
            		pathB[i].addr_print();
            		cout << "-->";
            		mult_depot.addr_print();
            		cout << endl;
          		}
          
        	}
         }
                                                      
                                                 
      
        
//     	//55.3
   /*
  		void optimized_route(){
       //O(n^3) time complexity
       	vector <Address> reverse_section;
       	vector <Address> temp_path;
       	vector <Address> shortest_path;
       	int short_dist = this->get_distance();
       	int i, j, k, q, r;
       	for (i = 0; i < addr_list.size(); i++){
       		for (j = i+1; j < addr_list.size(); j++){
             for (k = i; k <= j; k++){
             	reverse_section.push_back(addr_list[k]);
             }
             reverse(reverse_section.begin(),reverse_section.end());
             for (int x = 0; x < i; x++){
               temp_path.push_back(addr_list[x]);
             }
             for (int x = i; x <= j; x++){
               temp_path.push_back(reverse_section[i-x]);
             }
             for (int x = j+1; x < addr_list.size(); x++){
               temp_path.push_back(addr_list[x]);
             }
             AddressList* temp = new AddressList(temp_path);//added new constructor for AddressList that takes preconstructed list as parameter, check above
             if (temp->get_distance() < short_dist){//if length of new path is less than shortest path
               shortest_path.clear();
               for (int i = 0; i < addr_list.size(); i++){
                 shortest_path.push_back(temp_path[i]); //save entire path
               }
               short_dist = temp->get_distance(); //save distance of path
             }
             reverse_section.clear();
             temp_path.clear();
           }
         }
       	addr_path.clear();
       	addr_path.push_back(depot);
       	for (q = 0; q < shortest_path.size(); q++){
         	addr_path.push_back(shortest_path[q]); //new shortest path
         }
         addr_path.insert(addr_path.end(), depot); 
       		cout << "Optimized Route Path: ";
       		for(r = 0; r < addr_path.size(); r++){
           		addr_path[r].addr_print();
           		cout << " ";
         	}
         	cout << endl;
     	}
      
    	
    	int o(){
    // store all vertex apart from source vertex

          // store minimum weight Hamiltonian Cycle.
          int min_path = INT_MAX;
          do {
            

              // store current Path weight(cost)
              int current_pathweight = 0;

              // compute current path weight
              int k = s;
              for (int i = 0; i < vertex.size(); i++) {
                  current_pathweight += graph[k][vertex[i];
                  k = vertex[i];
              }
              current_pathweight += graph[k][s];

              // update minimum
              min_path = min(min_path, current_pathweight);

          } while (
              next_permutation(vertex.begin(), vertex.end()));

          return min_path;
				}*/
    	//55.6 super basic, it just finds the closest address then depending on if its closer to the address before or address after (x-1 or x+1) the new address gets placed before or after the closest address
      
     	void dynamic_addresses(Address x){
     		addr_list.clear();
     		for (int i = 1; i < addr_path.size()-1; i++){
     			addr_list.push_back(addr_path[i]);
     		}
     		addr_list.push_back(x);
     		cout << "Dynamically allocating Address (" << x.getI() << "," << x.getJ() << ")..." << endl;
     		this->greedy_route();
       	}
    	 	private:
   			int full_distance;
     	
 			};
 


int main(){

   int addr_count, addr_date, addr_i, addr_j, prime;
   int distance;
   int i = 0;
   cout << "How many addresses are initially included? ";
   cin >> addr_count;
   vector <Address> line;
   AddressList* pathA;
   AddressList* pathB;
   int signal = 0;
   for (int i = 0; i < addr_count; i++){
     cout << "Type ship date of Address " << i+1 << " , then the I and J coordinates of the address, then 1 if Prime Order or 0 if not." << endl;
     cin >> addr_date >> addr_i >> addr_j >> prime;
     while(prime!=0 && prime!=1){
       cout << "Error: Invalid statement for Prime" << endl;
       cin >> prime;
     }
     Address* temp = new Address(addr_date, addr_i, addr_j, prime);
     line.push_back(*temp);
     delete temp; 
   }
   cout << "Split Paths Between Day or Truck?" << endl;
   cin >> signal;
   cout << endl;
   cout << endl;
   cout << endl;
   cout << "***************************************************" << endl;
   cout << "         Analyzing Paths and Distances..." << endl;
   cout << "***************************************************" << endl;
   cout << endl;
   AddressList path(line);
   cout << "Greedy Route Distance: ";
   Route r1(line);
   r1.get_full_distance();
   r1.greedy_route();
   r1.multi_trucks(signal);
   r1.two_paths();
   r1.two_paths_w_prime();
   string ans;
   cout << "Would you like add more addresses? 'Y' for Yes 'N' for No" << endl;
   cin >> ans;
   while (ans == "Y"){
   	 cout << "Type ship date of Address " << i+1 << " , then the I and J coordinates of the address, then 1 if Prime Order or 0 if not." << endl;
     cin >> addr_date >> addr_i >> addr_j >> prime;
     while(prime!=0 && prime!=1){
       cout << "Error: Invalid statement for Prime" << endl;
       cin >> prime;
     }
     Address* temp = new Address(addr_date, addr_i, addr_j, prime);
     r1.dynamic_addresses(*temp);
     cout << "Would you like add more addresses? 'Y' for Yes 'N' for No" << endl;
   	 cin >> ans;
   }
   	cout << "Program Done" << endl;
   
   return 0;
}

