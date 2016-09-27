
class Camera
{
 private : 
  
  int etat;
  float rot_y;
  float rot_x;
  float ss;
  
 public : 
  
  Camera();
  void render_cam();
  
  void set_etat();
  void set_x(int s);
  void set_y(int s);
  void set_ss(int s);
  
  int get_etat();
};
