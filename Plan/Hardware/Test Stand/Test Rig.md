To determine the maximum Take Off Weight, a Motor Test Bench is required to measure the maximum thrust the motor, propeller, ESC, and battery combination can provide. To create a test rig, the following hardware is required:

1.  Load Cell
2.  Amplifier
3.  Test Bench Mount
4.  Arduino/Raspberry Pi

**Load Cell** The Load Cell consists of an aluminum bar and strain gauges. When the metal is deformed by the motor's load, the strain gauge changes its resistance, thereby altering the measured voltage. Since there is a range of sensitivity for Load Cells, I selected the highest expected thrust of the motor, which is 100N, added a safety margin, and chose the next closest sensitivity, which is 300N. I found the most suitable option at the best price on [Amazon](https://www.amazon.de/dp/B07L82YWPV?psc=1&ref=ppx_yo2ov_dt_b_product_details), which already included the amplifier.

**Amplifier** Because the voltage changes from the strain gauges are very subtle, an amplifier is necessary to increase the output voltage, making it measurable with an Arduino. The included amplifier is an HX711.

**Test Bench Mount** To attach the motor to the Load Cell, a custom-made mount is required. I created a 3D-model and 3D-printed the mount with PLA. The 3D model and technical drawing are included in the folder. Edit: During assembly, it was noticed that the Mount overlaps about 1mm with the glue of the strain gauge. As this already puts stress on the gauge, a few milimeters have to be sanded off the mount.
