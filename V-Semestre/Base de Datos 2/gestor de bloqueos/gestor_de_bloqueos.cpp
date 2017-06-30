#include <iostream>
#include <vector>
#include <utility>
using namespace std;

typedef vector<string> vec_s;
typedef vector<int> vec_i;
typedef pair<string,vec_s> pair_S_V;

struct data {
	bool bloqueado=false;
	char identificador;
	string dato_string="";
	std::vector<int> trans;

};
void read(data dato) {
	std::cout << "/* leendo dato */ "<<dato.dato_string << '\n';
}
void write(data dato,string new_data) {
	dato.dato_string=new_data;
	std::cout << "/* sobreescribiendo dato */ "<<dato.dato_string << '\n';
}
void wait(bool lock) {
	while (lock==true) {
		std::cout << "esperando" << '\n';
	}
}
void lock_X(data dato) {//bloqueo exclusivo
	dato.bloqueado=true;
}
void unlock_X(data dato) {//bloqueo exclusivo
	dato.bloqueado=false;
}

void lock_S(data dato) {//bloqueo compartido
	wait(dato.bloqueado);
	// dato.bloqueado=false;
}
typedef std::vector<vector<data>> gestor;

bool add_data(vector<data> vec,char id, string data_string){
	data new_data;
	new_data.identificador=id;
	new_data.dato_string=data_string;
	vec.push_back(new_data);
}

int main(int argc, char const *argv[]) {
  gestor my_manager(100);
	add_data(my_manager[0],'A',"informacion del dato A ");
	add_data(my_manager[1],'B',"informacion del dato B ");
  return 0;
}
