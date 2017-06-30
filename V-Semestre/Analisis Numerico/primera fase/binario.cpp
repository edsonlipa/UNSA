#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef  double number;
void bindecimal(number num)
{
	std::vector<pair<number,int>> v;
	int entero=(int)num;
	cout<<"----------este es el nuevo entero---------- "<<entero<<"."<<endl;
	number decimal=num-entero;
	// cout<<"-------------parte decimal---------- "<<decimal<<endl;
	int enteroaux;

	bool periodico=false;

	while (decimal!=0&&!periodico) {
		decimal=decimal*2;
		enteroaux=(int)decimal;
		std::cout << "entero auxiliar      "<<enteroaux << '\n';
		v.push_back(make_pair(decimal,entero));
		decimal=decimal-enteroaux;
		std::cout << "decimal                                " << decimal<<'\n';
	}
}
void binario(int num)
{
	vector<int> numbin;
	while(num>0)
	{
		numbin.push_back(num%2);
		//cout<<""<<num%2<<endl;
		num=num/2;
	}
	reverse(numbin.begin(),numbin.end());
	for (auto i : numbin)
	{
		cout<<i;
	}
}

int main(int argc, char const *argv[])
{

	bindecimal(0.2);
	return 0;
}
