 keyboardWidth = 349;   // PCB width
 keyboardHeight = 128;  // PCB height
 switchSize = 14;       // X or Y size of switch
 switchMargin = 5.05;   //Distance between switches (free space kept for keycap + small space)
 escPaddingX = 1.95;    //Distance between left edge of PCB and ESC
 escPaddingY = 5.09;    //Distance between top edge of PCB and ESC
 fkeysMargin = 14.57;   //Distance between Fkeys blocks
 navigationBlockMargin = 9.81;  //Distance between print screen and F12

keycapSize = switchSize + switchMargin; // Size of switch + margin for keycap
 
  difference()
  {
     cube([keyboardWidth, keyboardHeight, 1]);
     EscRow();
     TildaRow();
     TabRow();
     CapsLockRow();
     ShiftRow();
     CtrlRow();
  }

module switch1u(positionX, positionY)
{
    translate([positionX, keyboardHeight - switchSize - positionY, 0])
    {
        cube([switchSize, switchSize, 1]);
    }
}

module switch2u(positionX, positionY)
{
    translate([positionX, keyboardHeight - switchSize - positionY, 0])
    {
        cube([2*switchSize + switchMargin, switchSize, 1]);
    }
}

module EscRow()
{
    rowPositionY = escPaddingY;
    switch1u(escPaddingX + 0 * switchSize + 0 * switchMargin, rowPositionY);

    for (i = [2:1:5])
    {
       switch1u(0 * fkeysMargin + escPaddingX + i * keycapSize, rowPositionY);
    }

    for (i = [6:1:9])
    {
       switch1u(1 * fkeysMargin - switchMargin + escPaddingX + i * keycapSize, rowPositionY);
    }
     
    for (i = [10:1:13])
    {
       switch1u(2 * fkeysMargin - 2 * switchMargin + escPaddingX + i * keycapSize, rowPositionY);
    }
     
    for (i = [14:1:16])
    {
       switch1u(3 * navigationBlockMargin - switchMargin + escPaddingX + i * keycapSize, rowPositionY);
    }
}

module TildaRow()
{
    rowIndex = 2;
    rowPositionY = escPaddingY + rowIndex * switchSize + (rowIndex - 1) * switchMargin;
    
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
    rowPositionY = escPaddingY + rowIndex * switchSize + (rowIndex - 1) * switchMargin;
    
    for (i = [0:1:12])
    {
       switch1u(escPaddingX + i * switchSize + (i-1) * switchMargin, rowPositionY);
    }
    
    switch2u(escPaddingX + 13 * switchSize + (13-1) * switchMargin, rowPositionY);
    
    for (i = [14:1:16])
    {
       switch1u(3 * navigationBlockMargin - switchMargin + escPaddingX + i * switchSize + (i-1) * switchMargin, rowPositionY);
    }
}

module CapsLockRow()
{
    rowIndex = 4;
    rowPositionY = escPaddingY + rowIndex * switchSize + (rowIndex - 1) * switchMargin;
    
    for (i = [0:1:12])
    {
       switch1u(escPaddingX + i * switchSize + (i-1) * switchMargin, rowPositionY);
    }
    
    switch2u(escPaddingX + 13 * switchSize + (13-1) * switchMargin, rowPositionY);
}

module ShiftRow()
{
    rowIndex = 5;
    rowPositionY = escPaddingY + rowIndex * switchSize + (rowIndex - 1) * switchMargin;
    
    for (i = [0:1:12])
    {
       switch1u(escPaddingX + i * switchSize + (i-1) * switchMargin, rowPositionY);
    }
    
    switch2u(escPaddingX + 13 * switchSize + (13-1) * switchMargin, rowPositionY);
    
    i = 15;
    switch1u(3 * navigationBlockMargin - switchMargin + escPaddingX + i * switchSize + (i-1) * switchMargin, rowPositionY);
}

module CtrlRow()
{
    rowIndex = 6;
    rowPositionY = escPaddingY + rowIndex * switchSize + (rowIndex - 1) * switchMargin;
    
    for (i = [0:1:12])
    {
       switch1u(escPaddingX + i * switchSize + (i-1) * switchMargin, rowPositionY);
    }
    
    switch2u(escPaddingX + 13 * switchSize + (13-1) * switchMargin, rowPositionY);
    
    for (i = [14:1:16])
    {
       switch1u(3 * navigationBlockMargin - switchMargin + escPaddingX + i * switchSize + (i-1) * switchMargin, rowPositionY);
    }
}