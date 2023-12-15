Hexapod hexa;

void setup() {
  size(1000, 1000);
  smooth();
  hexa = new Hexapod();
  renderUI();
}

void draw() {          

  pushMatrix();
  translate(width/2, height/2);
  background(0); 
  
  hexa.update();
  renderHexapod(hexa);
  
  popMatrix();
}