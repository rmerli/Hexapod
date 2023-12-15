import controlP5.*;

int sliderThickness = 20;
int sliderLength = 150;
int padding = 2;



Slider sx;
Slider sy;
Slider sz;

ControlP5 ui;
void renderUI() {
  ui = new ControlP5(this);
  
     
  sx = ui.addSlider("angleX").
    setPosition(0,height-(sliderThickness * 3) - (padding * 2 ))
    .setWidth(sliderLength)
    .setHeight(sliderThickness)
    .setRange(-PI,PI)
    .setValue(0);
    
  //  sy = ui.addSlider("angleY").
  //   setPosition(0,height-(sliderThickness * 2) - padding)
  //   .setWidth(sliderLength)
  //   .setHeight(sliderThickness)
  //   .setRange(-PI,PI)
  //   .setValue(0);
    
  sz = ui.addSlider("angleZ").
    setPosition(0,height-(sliderThickness))
    .setWidth(sliderLength)
    .setHeight(sliderThickness)
    .setRange(-PI,PI)
    .setValue(0);

    
      ui.addSlider("distance").
    setPosition(200,height-(sliderThickness))
    .setWidth(sliderLength)
    .setHeight(sliderThickness)
    .setRange(3,0)
    .setValue(0.96);
    
    ui.addButton("reset")
    .setPosition(0,height-(sliderThickness * 4) - (padding * 3 ));

    ui.addButton("startWalking")
    .setPosition(width - 100,height-(sliderThickness * 6) - (padding * 3 ));

    ui.addButton("stop")
    .setPosition(width - 100, height-(sliderThickness * 5) - (padding * 3 ));
}

void reset() {
  angleX = 1.2;
  angleY = 0;
  angleZ = 1;
   distance = 1.2;
}

void startWalking() {
  hexa.walk();
}

void stop() {
  hexa.stop();
}
