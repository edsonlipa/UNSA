#include <iostream>
#include <map>
#include <vector>
#include <SFML/Graphics.hpp>
using namespace std;

typedef map<int,map<int,int> > points;
typedef vector<int > veci;
typedef vector<string > vecs;
typedef vector<veci > matrix;
typedef vector<vector<veci > > matrixs_vector;
#define n 30
#define DimensionWindow 500


void print_vect(veci v) {
  cout << "[";for(auto i:v){
  cout <<i<< ",";}
  cout << "]\n";
}

void print_matrix(matrix m){
  for (size_t i = 0; i < m.size(); i++) {
    std::cout << "["<<i<<"]";
    print_vect(m[i]);
  }
  std::cout  << '\n';
}

veci matrix_to_vector(matrix matriz) {
  // std::veci convertido(matriz.size()*matriz[0].size());
  veci convertido;
  for (size_t i = 0; i < matriz.size(); i++) {
    for (size_t j = 0; j < matriz.size(); j++) {
      convertido.push_back(matriz[i][j]);
    }
  }
  return convertido;
}
matrix vector_to_matrix(veci vec) {
  // std::veci convertido(matriz.size()*matriz[0].size());
  int size=2;
  matrix convertido(size,veci(size));
  int k=0;
  for (size_t i = 0; i < size; i++) {
    for (size_t j = 0; j < size; j++) {
      convertido[i][j]=vec[k]; k++;
    }
  }
  return convertido;
}

matrix multbyinverse(veci v){
  matrix ans(v.size(),veci (v.size()));
  for (size_t i = 0; i < v.size(); i++) {
    for (size_t j = 0; j < v.size(); j++) {
      ans[i][j]=v[i]*v[j];
    }
  }
  return ans;
}

veci operator *(veci v1,matrix m2){
  veci ans(v1.size());
  for (size_t i = 0; i < m2.size(); i++) {
    float sum=0;
    for (size_t j = 0; j < m2[0].size(); j++) {
      sum+=m2[j][i]*v1[j];
    }
    ans[i]=sum;
  }
  return ans;
}matrix operator -(matrix m1,matrix m2){
  matrix ans(m1.size(),veci (m1.size()));
  for (size_t i = 0; i < m1.size(); i++) {
    for (size_t j = 0; j < m1.size(); j++) {
      ans[i][j]=m1[i][j]-m2[i][j];
    }
  }
  return ans;
}
matrix operator +(matrix m1,matrix m2){
  matrix ans(m1.size(),veci (m1.size()));
  for (size_t i = 0; i < m1.size(); i++) {
    for (size_t j = 0; j < m1.size(); j++) {
      ans[i][j]=m1[i][j]+m2[i][j];
    }
  }
  return ans;
}

matrix identidad(int n1){
  matrix ans(n1,veci (n1));
  for (size_t i = 0; i < n1; i++) {
    ans[i][i]=1;
  }
  return ans;
}

matrix train(matrix inputs) {
  matrixs_vector container;
  std::cout << "bien" << '\n';
  for ( auto i:inputs ) {
    std::cout << multbyinverse(i).size()<<" /* message */ " << '\n';
    container.push_back(multbyinverse(i)-identidad(i.size()));
  }
  int size_of_input=inputs[0].size();
  matrix ans(size_of_input,veci(size_of_input));
  for (auto i:container){
    ans=ans+i;
  }
  return ans;
}
veci recordar(veci in,matrix hopfield){
  veci nuevo=in*hopfield;
  for (auto &i:nuevo ) {
    if (i>0) i=1;
    else i=-1;
  }
  return nuevo;
}

void save_point(int a, int y) {
  std::cout << "/* message */" << '\n';
}
bool operator < (sf::Color color1,sf::Color color2)
{
  if (color1.r<color2.r&&color1.g<color2.g&&color1.b<color2.b) {
    return true;
  }
  return false;
}
void draw_new_shape(sf::RenderWindow& window,int x,int y) {
  sf::CircleShape shape(n);
  shape.setFillColor(sf::Color::Black);
  shape.setOrigin(n,n);
  shape.setPosition(x,y);
  window.draw(shape);
}
matrix  get_matrix_from_img(sf::Image photo){
  matrix wind_matriz(DimensionWindow,vector<int> (DimensionWindow));
  sf::Color Negro(50,50,50);
  for (size_t i = 0; i < DimensionWindow; i++) {
    for (size_t j = 0; j < DimensionWindow; j++) {
      // std::cout <<photo.getPixel(i,j).r<< " " <<photo.getPixel(i,j).g<<" "<<photo.getPixel(i,j).b <<'\n';
      if (photo.getPixel(i,j)<Negro) {wind_matriz[i][j]=1;}
      else{wind_matriz[i][j]=-1;}
    }
  }
  return wind_matriz;
}
sf::Image get_img_from_matrix(matrix wind_matriz){
  sf::Image photo;
  photo.create(500,500);
  for (size_t i = 0; i < DimensionWindow; i++) {
    for (size_t j = 0; j < DimensionWindow; j++) {
      if (wind_matriz[i][j]==1){photo.setPixel(i,j,sf::Color::Black);}
      else{photo.setPixel(i,j,sf::Color::White);}
    }
  }
  return photo;
}
matrix init_window() {
  sf::RenderWindow window(sf::VideoMode(DimensionWindow, DimensionWindow), "Input-Number");
  sf::CircleShape shape(n);
  shape.setFillColor(sf::Color::Green);
  shape.setOrigin(n,n);
  int x;
  int y;
  bool dibujar=false;
  points wind_points;
  sf::Image photo;
  sf::Texture texture;
  texture.create(DimensionWindow, DimensionWindow);
    while (window.isOpen())
    {
      sf::Event event;
      while (window.pollEvent(event))
      {
          if (event.type == sf::Event::MouseMoved){
              x=event.mouseMove.x;
              y=event.mouseMove.y;
              if (x<DimensionWindow&&y<DimensionWindow&&x>0&&y>0) {
                shape.setPosition(x,y);
                if (dibujar) {wind_points[x][y]=1;}
              }
          }
          if (event.type == sf::Event::MouseButtonReleased) {dibujar=false;}
          if (event.type == sf::Event::MouseButtonPressed) {dibujar=true;}
          if (event.type == sf::Event::Closed)
              window.close();
      }
      window.clear(sf::Color::White);
      for (auto i:wind_points ) {
        for (auto j:i.second ) {
          draw_new_shape(window,i.first,j.first);
        }
      }
      texture.update(window);
      photo = texture.copyToImage();
      window.draw(shape);
      window.display();
    }
    if (!photo.saveToFile("photo.jpg")) std::cout << "error al guardar" << '\n';


  return get_matrix_from_img(photo);
}
matrix loadImgtoMatrix(string name) {
  sf::Image photo;
  photo.loadFromFile(name);
  return get_matrix_from_img(photo);
}
void draw(sf::Image &photo) {

    sf::RenderWindow window(sf::VideoMode(500, 500), "SFML window");
    // sf::Image photo;
    // photo.loadFromFile("Numero2.jpg");
    // photo=get_img_from_matrix(loadImgtoMatrix("Numero1.jpg"));
    sf::Texture texture;
    texture.loadFromImage(photo);
    sf::Sprite sprite;
    sprite.setTexture(texture);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(sprite);
        window.display();
    }
}
void run() {

  vecs names={"Numero1.jpg","Numero2.jpg"};
  matrix inputs;
  for (auto i:names )
  {inputs.push_back(matrix_to_vector( loadImgtoMatrix(i)));}

  matrix hopfield=train(inputs);
  // matrix inputmatrix=init_window();
  // veci input1=matrix_to_vector(inputmatrix);
  // print_matrix(hopfield);
  // print_vect(recordar(input1,hopfield));
  // sf::Image result=get_img_from_matrix(vector_to_matrix(recordar(input1,hopfield)));
  // draw(result);

}
int main()
{
    run();
    // matrix window;
    // window=init_window();
    // get_matrix();

    return 0;
}
