projection(cut=true) { plate(); }

switchSizes = [
    [1, [14, 14]],
    [1.25, [17.5, 14]],
    [1.5, [21, 14]],
    [1.75, [24.5, 14]],
    [2.25, [31.5, 14]]
];

1uSize = switchSizes[search(1, switchSizes)[0]][1];
1_25uSize = switchSizes[search(1.25, switchSizes)[0]][1];
1_5uSize = switchSizes[search(1.5, switchSizes)[0]][1];
1_75uSize = switchSizes[search(1.75, switchSizes)[0]][1];
2_25uSize = switchSizes[search(2.25, switchSizes)[0]][1];

cutSize = [7, 15];

defaultSeparator = 5.05;
blockSeparator = 0.5 * (1uSize[0] + defaultSeparator);
navigationSeparator = 0.25 * (1uSize[0] + defaultSeparator);
cutoutSeparator = 1.44;

module u(multiplier, x, y)
{
    switchSize = switchSizes[search(multiplier, switchSizes)[0]][1];
    
    translate([x, -y, 0])
    { 
        finalX = switchSize[0];
        finalY = switchSize[1] ;
        
        cube([finalX, finalY, 1]);
    }
}

module c(x, y)
{
    translate([x, -y, 0])
    { 
        cube([7, 15, 1]);
    }
}

module plate()
{
    row0();
    row1();
    row2();
    row3();
    row4();
    row5();
}

module row0()
{
    rowIndex = 0;
    offsetY = rowIndex * 1uSize[1];
    
    u(1, 0 * (1uSize[0] + defaultSeparator), offsetY);

    u(1, 2 * (1uSize[0] + defaultSeparator), offsetY);
    u(1, 3 * (1uSize[0] + defaultSeparator), offsetY);
    u(1, 4 * (1uSize[0] + defaultSeparator), offsetY);
    u(1, 5 * (1uSize[0] + defaultSeparator), offsetY);
    
    u(1, 6 * (1uSize[0] + defaultSeparator) + blockSeparator, offsetY);
    u(1, 7 * (1uSize[0] + defaultSeparator) + blockSeparator, offsetY);
    u(1, 8 * (1uSize[0] + defaultSeparator) + blockSeparator, offsetY);
    u(1, 9 * (1uSize[0] + defaultSeparator) + blockSeparator, offsetY);
    
    u(1, 10 * (1uSize[0] + defaultSeparator) + 2 * blockSeparator, offsetY);
    u(1, 11 * (1uSize[0] + defaultSeparator) + 2 * blockSeparator, offsetY);
    u(1, 12 * (1uSize[0] + defaultSeparator) + 2 * blockSeparator, offsetY);
    u(1, 13 * (1uSize[0] + defaultSeparator) + 2 * blockSeparator, offsetY);
    
    u(1, 14 * (1uSize[0] + defaultSeparator) + 2 * blockSeparator + navigationSeparator, offsetY);
    u(1, 15 * (1uSize[0] + defaultSeparator) + 2 * blockSeparator + navigationSeparator, offsetY);
    u(1, 16 * (1uSize[0] + defaultSeparator) + 2 * blockSeparator + navigationSeparator, offsetY);
}

module row1()
{
    rowIndex = 1;
    offsetY = rowIndex * 1uSize[1] + blockSeparator + defaultSeparator;
    leftCutOffsets = [cutoutSeparator + cutSize[0], cutSize[1] - 1uSize[1]];
    rightCutOffsets = [cutoutSeparator + 1uSize[0], cutSize[1] - 1uSize[1]];
    
    u(1, 0 * (1uSize[0] + defaultSeparator), offsetY);
    u(1, 1 * (1uSize[0] + defaultSeparator), offsetY);
    u(1, 2 * (1uSize[0] + defaultSeparator), offsetY);
    u(1, 3 * (1uSize[0] + defaultSeparator), offsetY);
    u(1, 4 * (1uSize[0] + defaultSeparator), offsetY);
    u(1, 5 * (1uSize[0] + defaultSeparator), offsetY);
    
    u(1, 6 * (1uSize[0] + defaultSeparator), offsetY);
    u(1, 7 * (1uSize[0] + defaultSeparator), offsetY);
    u(1, 8 * (1uSize[0] + defaultSeparator), offsetY);
    u(1, 9 * (1uSize[0] + defaultSeparator), offsetY);
    
    u(1, 10 * (1uSize[0] + defaultSeparator), offsetY);
    u(1, 11 * (1uSize[0] + defaultSeparator), offsetY);
    u(1, 12 * (1uSize[0] + defaultSeparator), offsetY);
    c(13 * (1uSize[0] + defaultSeparator) + blockSeparator - leftCutOffsets[0], offsetY + leftCutOffsets[1]);
    u(1, 13 * (1uSize[0] + defaultSeparator) + blockSeparator, offsetY);
    c(13 * (1uSize[0] + defaultSeparator) + blockSeparator + rightCutOffsets[0], offsetY + rightCutOffsets[1]);
    
    u(1, 14 * (1uSize[0] + defaultSeparator) + 2 * blockSeparator + navigationSeparator, offsetY);
    u(1, 15 * (1uSize[0] + defaultSeparator) + 2 * blockSeparator + navigationSeparator, offsetY);
    u(1, 16 * (1uSize[0] + defaultSeparator) + 2 * blockSeparator + navigationSeparator, offsetY);
}


module row2()
{
    rowIndex = 2;
    
    offsetX = 1 * (1_5uSize[0] + defaultSeparator);
    offsetY = rowIndex * 1uSize[1] + rowIndex * defaultSeparator + blockSeparator;
    
    u(1.5, 0 * (1uSize[0] + defaultSeparator), offsetY);
    u(1, offsetX + 0 * (1uSize[0] + defaultSeparator), offsetY);
    u(1, offsetX + 1 * (1uSize[0] + defaultSeparator), offsetY);
    u(1, offsetX + 2 * (1uSize[0] + defaultSeparator), offsetY);
    u(1, offsetX + 3 * (1uSize[0] + defaultSeparator), offsetY);
    u(1, offsetX + 4 * (1uSize[0] + defaultSeparator), offsetY);
    
    u(1, offsetX + 5 * (1uSize[0] + defaultSeparator), offsetY);
    u(1, offsetX + 6 * (1uSize[0] + defaultSeparator), offsetY);
    u(1, offsetX + 7 * (1uSize[0] + defaultSeparator), offsetY);
    u(1, offsetX + 8 * (1uSize[0] + defaultSeparator), offsetY);
    
    u(1, offsetX + 9 * (1uSize[0] + defaultSeparator), offsetY);
    u(1, offsetX + 10 * (1uSize[0] + defaultSeparator), offsetY);
    u(1, offsetX + 11 * (1uSize[0] + defaultSeparator), offsetY);
    u(1, offsetX + 12 * (1uSize[0] + defaultSeparator), offsetY);
    
    u(1, 14 * (1uSize[0] + defaultSeparator) + 2 * blockSeparator + navigationSeparator, offsetY);
    u(1, 15 * (1uSize[0] + defaultSeparator) + 2 * blockSeparator + navigationSeparator, offsetY);
    u(1, 16 * (1uSize[0] + defaultSeparator) + 2 * blockSeparator + navigationSeparator, offsetY);
}
    
module row3()
{
    rowIndex = 3;
    offsetX = 1 * (1_75uSize[0] + defaultSeparator);
    offsetY = rowIndex * 1uSize[1] + rowIndex * defaultSeparator + blockSeparator;
    
    u(1.75, 0 * (1uSize[0] + defaultSeparator), offsetY);
    u(1, offsetX + 0 * (1uSize[0] + defaultSeparator), offsetY);
    u(1, offsetX + 1 * (1uSize[0] + defaultSeparator), offsetY);
    u(1, offsetX + 2 * (1uSize[0] + defaultSeparator), offsetY);
    u(1, offsetX + 3 * (1uSize[0] + defaultSeparator), offsetY);
    u(1, offsetX + 4 * (1uSize[0] + defaultSeparator), offsetY);
    
    u(1, offsetX + 5 * (1uSize[0] + defaultSeparator), offsetY);
    u(1, offsetX + 6 * (1uSize[0] + defaultSeparator), offsetY);
    u(1, offsetX + 7 * (1uSize[0] + defaultSeparator), offsetY);
    u(1, offsetX + 8 * (1uSize[0] + defaultSeparator), offsetY);
    
    u(1, offsetX + 9 * (1uSize[0] + defaultSeparator), offsetY);
    u(1, offsetX + 10 * (1uSize[0] + defaultSeparator), offsetY);
    u(1, offsetX + 11 * (1uSize[0] + defaultSeparator), offsetY);
    u(1, offsetX + 12 * (1uSize[0] + defaultSeparator), offsetY);
}

module row4()
{
    rowIndex = 4;
    offsetX = 1 * (2_25uSize[0] + defaultSeparator);
    offsetY = rowIndex * 1uSize[1] + rowIndex * defaultSeparator + blockSeparator;
    
    u(2.25, 0 * (1uSize[0] + defaultSeparator), offsetY);
    u(1, offsetX + 0 * (1uSize[0] + defaultSeparator), offsetY);
    u(1, offsetX + 1 * (1uSize[0] + defaultSeparator), offsetY);
    u(1, offsetX + 2 * (1uSize[0] + defaultSeparator), offsetY);
    u(1, offsetX + 3 * (1uSize[0] + defaultSeparator), offsetY);
    u(1, offsetX + 4 * (1uSize[0] + defaultSeparator), offsetY);
    
    u(1, offsetX + 5 * (1uSize[0] + defaultSeparator), offsetY);
    u(1, offsetX + 6 * (1uSize[0] + defaultSeparator), offsetY);
    u(1, offsetX + 7 * (1uSize[0] + defaultSeparator), offsetY);
    u(1, offsetX + 8 * (1uSize[0] + defaultSeparator), offsetY);
    
    u(1, offsetX + 9 * (1uSize[0] + defaultSeparator), offsetY);
    u(1, offsetX + 10 * (1uSize[0] + defaultSeparator), offsetY);
    u(1, offsetX + 11 * (1uSize[0] + defaultSeparator), offsetY);
    u(1, offsetX + 12 * (1uSize[0] + defaultSeparator), offsetY);
    
    u(1, 15 * (1uSize[0] + defaultSeparator) + 2 * blockSeparator + navigationSeparator, offsetY);
}

module row5()
{
    rowIndex = 5;
    offsetX = (1_25uSize[0] + defaultSeparator);
    offsetY = rowIndex * 1uSize[1] + rowIndex * defaultSeparator + blockSeparator;
    
    u(1.25, 0 * (1uSize[0] + defaultSeparator), offsetY);
    u(1.25, 1 * offsetX + 0 * (1uSize[0] + defaultSeparator), offsetY);
    u(1.25, 2 * offsetX + 1 * (1uSize[0] + defaultSeparator), offsetY);
    u(1, 2 * offsetX + 2 * (1uSize[0] + defaultSeparator), offsetY);
    u(1, 2 * offsetX + 3 * (1uSize[0] + defaultSeparator), offsetY);
    u(1, 2 * offsetX + 4 * (1uSize[0] + defaultSeparator), offsetY);
    
    u(1, 2 * offsetX + 5 * (1uSize[0] + defaultSeparator), offsetY);
    u(1, 2 * offsetX + 6 * (1uSize[0] + defaultSeparator), offsetY);
    u(1, 2 * offsetX + 7 * (1uSize[0] + defaultSeparator), offsetY);
    u(1, 2 * offsetX + 8 * (1uSize[0] + defaultSeparator), offsetY);
    
    u(1, 2 * offsetX + 9 * (1uSize[0] + defaultSeparator), offsetY);
    u(1, 2 * offsetX + 10 * (1uSize[0] + defaultSeparator), offsetY);
    u(1, 2 * offsetX + 11 * (1uSize[0] + defaultSeparator), offsetY);
    u(1, 2 * offsetX + 12 * (1uSize[0] + defaultSeparator), offsetY);
    
    u(1, 14 * (1uSize[0] + defaultSeparator) + 2 * blockSeparator + navigationSeparator, offsetY);
    u(1, 15 * (1uSize[0] + defaultSeparator) + 2 * blockSeparator + navigationSeparator, offsetY);
    u(1, 16 * (1uSize[0] + defaultSeparator) + 2 * blockSeparator + navigationSeparator, offsetY);
}