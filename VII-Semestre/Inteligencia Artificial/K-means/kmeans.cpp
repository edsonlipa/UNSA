#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <time.h>
#include <vector>
#include <fstream>
#include <string>
#include <unistd.h>

using namespace std;

#define window_w 2000
#define window_h 1000
#define radius 5

typedef std::vector<float> vecf;
typedef std::vector<sf::Color> vecC;
typedef std::vector<vecf> matrix;

#define xscale 8
#define yscale 6

float pointx(float n){
  // return (window_w/xscale)*n;
  return ((window_w/xscale)*n)-((window_w/xscale)*2);
}
float pointy(float n){
  return window_h-((window_h/yscale)*n);
}
void print_data(matrix di,vecC dout){
  int count=0;
  for(int i=0;i<di.size();i++){
    for(int j=0;j<di[i].size();j++){

      cout<<di[i][j]<<"   ";
    }
    count++;
    cout<<"\t\t-> \t";
    if (dout[i]==sf::Color::Red) {
      std::cout << "Iris-setosa"<<" Rojo " ;
    } else if (dout[i]==sf::Color::Green) {
      std::cout << "Iris-versicolor"<<" Green" ;
    } else {
      std::cout << "Iris-virginica" << " Blue";
    }
    cout<<endl;
  }
  std::cout << count<<" registros" << '\n';

}
void leer_data(matrix &di,vecC &Colors){

	ifstream file("database_iris.in");
	char c;string p="";int cont=0;

	vecf aux;

	int act=1;
  aux.push_back(1);
	if(file.is_open())
  	{
    	while ( file.get (c) ){
      		if(c!=',' && c!='\n'){p+=c;}
      		else{
      			if(cont<4){
              if (cont<2) {
                aux.push_back(strtof(p.c_str(),0));
              }cont++;
      			}
      			else{
      				di.push_back(aux);
      				if(p=="Iris-setosa"){Colors.push_back(sf::Color::Red);}
      				else if(p=="Iris-versicolor"){Colors.push_back(sf::Color::Green);}
      				else{Colors.push_back(sf::Color::Blue);}
      				aux.clear();
      				cont=0;
      				act++;
      			}
      			p="";
      		}
    	}file.close();
  	}
}
void draw_layer(sf::RenderWindow& window) {
  for (size_t i = 1; i < xscale; i++) {
      for (size_t j = 1; j < yscale; j++) {
        sf::CircleShape shape(radius);
        shape.setFillColor(sf::Color::Black);
        shape.setOrigin(radius,radius);
        shape.setPosition(pointx(i),pointy(j));
        window.draw(shape);

      }
  }
}
void draw_input(sf::RenderWindow& window,matrix in,vecC Color) {
  for (size_t i = 1; i < in.size(); i++) {
        sf::CircleShape shape(radius);
        shape.setFillColor(sf::Color::Black);
        // shape.setFillColor(Color[i]);
        shape.setOutlineColor(Color[i]);
        shape.setOutlineThickness(1);

        shape.setOrigin(radius,radius);
        shape.setPosition(pointx(in[i][0]),pointy(in[i][1]));
        window.draw(shape);
  }
}
void init_centers(matrix &centers) {
  for (size_t i = 0; i < 3; i++) {
      centers[i][0]=2+((rand()%((xscale-2)*10))/10.0);
      centers[i][1]=rand()%(yscale*10)/10.0;
      std::cout << centers[i][0]<<" :: "<<centers[i][1] << '\n';
  }
}
void plot(matrix data_in,vecC Colors) {
  // Create the main window
  sf::RenderWindow window(sf::VideoMode(window_w, window_h), "SFML window");
  // Load a sprite to display
  // sf::Texture texture;
  // if (!texture.loadFromFile("cute_image.jpg"))
  //     return EXIT_FAILURE;
  // sf::Sprite sprite(texture);
  sf::CircleShape circle;
  // Start the game loop
  while (window.isOpen())
  {   // Process events
      sf::Event event;
      while (window.pollEvent(event))
      {
          // Close window: exit
          if (event.type == sf::Event::Closed)
              window.close();
      }
      // Clear screen
      window.clear(sf::Color::White);
      // Draw the sprite
      // draw_layer(window);
      draw_input(window,data_in,Colors);
      window.draw(circle);
      // Update the window
      window.display();
  }

}
int main(int argc, char const *argv[]) {
  srand(time(NULL));

  matrix data_input;
  vecC Colors;
  matrix centers(3,vecf(2));
  leer_data(data_input,Colors);
  init_centers(centers);
  // plot(data_input,Colors);


  // print_data(data_input,Colors);

    return 0;
}
