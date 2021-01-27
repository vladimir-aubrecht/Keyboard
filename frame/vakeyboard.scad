projection(cut=true) { plate(); }

 plateWidth = 349;   // Plate width
 plateHeight = 128;  // Plate height
 plateDepth = 1;     // Plate depth
 switchSize = 14;       // X or Y size of switch
 switchMargin = 5.05;   //Distance between switches (free space kept for keycap + small space)
 escPaddingX = 1.95;    //Distance between left edge of PCB and ESC
 escPaddingY = 5.09;    //Distance between top edge of PCB and ESC
 fkeysMargin = 14.57;   //Distance between Fkeys blocks
 navigationBlockMargin = 9.81;  //Distance between print screen and F12

keycapSize = switchSize + switchMargin; // Size of switch + margin for keycap

//plate();
 
 module plate()
 {
  difference()
  {
     cube([plateWidth, plateHeight, 1]);
     EscRow();
     TildaRow();
     TabRow();
     CapsLockRow();
     ShiftRow();
     CtrlRow();
  }
}

module switch1u(positionX, positionY)
{
    translate([positionX, plateHeight - switchSize - positionY, 0])
    {
        cube([switchSize, switchSize, plateDepth]);
    }
}

module switch1_25u(positionX, positionY)
{
    translate([positionX + 0.25*0.5*keycapSize, plateHeight - switchSize - positionY, 0])
    {
        cube([switchSize, switchSize, plateDepth]);
    }
}

module switch1_5u(positionX, positionY)
{
    translate([positionX + 0.25*keycapSize, plateHeight - switchSize - positionY, 0])
    {
        cube([switchSize, switchSize, plateDepth]);
    }
}

module switch1_75u(positionX, positionY)
{
    translate([positionX + 0.75*0.5*keycapSize, plateHeight - switchSize - positionY, 0])
    {
        cube([switchSize, switchSize, plateDepth]);
    }
}

module switch2u(positionX, positionY)
{
    translate([positionX + 0.5*keycapSize, plateHeight - switchSize - positionY, 0])
    {
        cube([switchSize, switchSize, plateDepth]);
    }
}

module switch2_25u(positionX, positionY)
{
    translate([positionX + 1.25*0.5*keycapSize, plateHeight - switchSize - positionY, 0])
    {
        cube([switchSize, switchSize, plateDepth]);
    }
}

module switch6_25u(positionX, positionY)
{
    translate([positionX + 5.25*0.5*keycapSize, plateHeight - switchSize - positionY, 0])
    {
        cube([switchSize, switchSize, plateDepth]);
    }
}

module EscRow()
{
    rowPositionY = escPaddingY;
    switch1u(escPaddingX + 0 * switchSize + 0 * switchMargin, rowPositionY);

    for (i = [2:1:5])
    {
       for (keyIndex = [0:1:2])
       {
           blockPadding = keyIndex * fkeysMargin + escPaddingX - keyIndex * switchMargin;
           keyPadding = (i + keyIndex * 4) * keycapSize;
           
           switch1u(blockPadding + keyPadding, rowPositionY);
       }
    }

    for (i = [14:1:16])
    {
       switch1u(3 * navigationBlockMargin + escPaddingX - switchMargin + i * keycapSize, rowPositionY);
    }
}

module TildaRow()
{
    rowIndex = 2;
    rowPositionY = escPaddingY + rowIndex * switchSize + (rowIndex - 2) * switchMargin;
    
    for (i = [0:1:12])
    {
       switch1u(escPaddingX + i * keycapSize, rowPositionY);
    }
    
    switch2u(escPaddingX + 13 * keycapSize, rowPositionY);
    
    for (i = [14:1:16])
    {
       switch1u(3 * navigationBlockMargin - switchMargin + escPaddingX + i * keycapSize, rowPositionY);
    }
}

module TabRow()
{
    rowIndex = 3;
    rowPositionY = escPaddingY + rowIndex * switchSize + (rowIndex - 2) * switchMargin;
    offsetX = 1.5*switchSize + switchMargin;
    
    switch1_5u(escPaddingX + 0 * keycapSize, rowPositionY);
    
    for (i = [0:1:11])
    {
       switch1u(offsetX + escPaddingX + i * keycapSize, rowPositionY);
    }
    
    switch1_5u(offsetX + escPaddingX + 12 * keycapSize, rowPositionY);
    
    for (i = [14:1:16])
    {
       switch1u(3 * navigationBlockMargin - switchMargin + escPaddingX + i * keycapSize, rowPositionY);
    }
}

module CapsLockRow()
{
    rowIndex = 4;
    rowPositionY = escPaddingY + rowIndex * switchSize + (rowIndex - 2) * switchMargin;
    offsetX = 1.75*switchSize + switchMargin;
    
    switch1_75u(escPaddingX + 0 * keycapSize, rowPositionY);
    
    for (i = [0:1:10])
    {
       switch1u(offsetX + escPaddingX + i * keycapSize, rowPositionY);
    }
    
    switch2_25u(offsetX + escPaddingX + 11 * keycapSize, rowPositionY);
}

module ShiftRow()
{
    rowIndex = 5;
    rowPositionY = escPaddingY + rowIndex * switchSize + (rowIndex - 2) * switchMargin;
    offsetX = 2.25*switchSize + switchMargin;
    
    switch2_25u(escPaddingX + 0 * keycapSize, rowPositionY);
    
    for (i = [0:1:9])
    {
       switch1u(offsetX + escPaddingX + i * keycapSize, rowPositionY);
    }
    
    switch2_25u(offsetX + switchMargin + escPaddingX + 10 * keycapSize, rowPositionY);
    
    i = 15;
    switch1u(3 * navigationBlockMargin - switchMargin + escPaddingX + i * keycapSize, rowPositionY);
}

module CtrlRow()
{
    rowIndex = 6;
    rowPositionY = escPaddingY + rowIndex * switchSize + (rowIndex - 2) * switchMargin;
    offsetX1_25 = 1.25*switchSize + switchMargin;
    offsetX6_25 = 6.25*switchSize + switchMargin;
    
    for (i = [0:1:2])
    {
       switch1_25u(i * offsetX1_25 + escPaddingX, rowPositionY);
    }
    
    switch6_25u(3 * offsetX1_25 + escPaddingX, rowPositionY);
    
    for (i = [0:1:3])
    {
       switch1_25u(3 * offsetX1_25 + 6.25*keycapSize - 0.5 * switchMargin + escPaddingX + i * offsetX1_25, rowPositionY);
    }
    
    for (i = [14:1:16])
    {
       switch1u(3 * navigationBlockMargin - switchMargin + escPaddingX + i * keycapSize, rowPositionY);
    }
}