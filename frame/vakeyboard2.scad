projection(cut=true) { plate(); }

switchSizes = [
    [1, [14, 14]],
    [1.25, [17.5, 14]],
    [1.5, [21, 14]],
    [1.75, [24.5, 14]],
    [2.25, [31.5, 14]]
];

1uSizes = switchSizes[search(1, switchSizes)[0]][1];
1_25uSizes = switchSizes[search(1.25, switchSizes)[0]][1];
1_5uSizes = switchSizes[search(1.5, switchSizes)[0]][1];
1_75uSizes = switchSizes[search(1.75, switchSizes)[0]][1];
2_25uSizes = switchSizes[search(2.25, switchSizes)[0]][1];

defaultSeparator = 5.05;

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

module plate()
{
    row0();
    row2();
    row3();
    row4();
    row5();
    row6();
}

module row0()
{
    rowIndex = 0;
    u(1, 0 * (1uSizes[0] + defaultSeparator), rowIndex * 1uSizes[1]);

    u(1, 2 * (1uSizes[0] + defaultSeparator), rowIndex * 1uSizes[1]);
    u(1, 3 * (1uSizes[0] + defaultSeparator), rowIndex * 1uSizes[1]);
    u(1, 4 * (1uSizes[0] + defaultSeparator), rowIndex * 1uSizes[1]);
    u(1, 5 * (1uSizes[0] + defaultSeparator), rowIndex * 1uSizes[1]);
    
    u(1, 6 * (1uSizes[0] + defaultSeparator), rowIndex * 1uSizes[1]);
    u(1, 7 * (1uSizes[0] + defaultSeparator), rowIndex * 1uSizes[1]);
    u(1, 8 * (1uSizes[0] + defaultSeparator), rowIndex * 1uSizes[1]);
    u(1, 9 * (1uSizes[0] + defaultSeparator), rowIndex * 1uSizes[1]);
    
    u(1, 10 * (1uSizes[0] + defaultSeparator), rowIndex * 1uSizes[1]);
    u(1, 11 * (1uSizes[0] + defaultSeparator), rowIndex * 1uSizes[1]);
    u(1, 12 * (1uSizes[0] + defaultSeparator), rowIndex * 1uSizes[1]);
    u(1, 13 * (1uSizes[0] + defaultSeparator), rowIndex * 1uSizes[1]);
}

module row2()
{
    rowIndex = 2;
    
    u(1, 0 * (1uSizes[0] + defaultSeparator), rowIndex * 1uSizes[1]);
    u(1, 1 * (1uSizes[0] + defaultSeparator), rowIndex * 1uSizes[1]);
    u(1, 2 * (1uSizes[0] + defaultSeparator), rowIndex * 1uSizes[1]);
    u(1, 3 * (1uSizes[0] + defaultSeparator), rowIndex * 1uSizes[1]);
    u(1, 4 * (1uSizes[0] + defaultSeparator), rowIndex * 1uSizes[1]);
    u(1, 5 * (1uSizes[0] + defaultSeparator), rowIndex * 1uSizes[1]);
    
    u(1, 6 * (1uSizes[0] + defaultSeparator), rowIndex * 1uSizes[1]);
    u(1, 7 * (1uSizes[0] + defaultSeparator), rowIndex * 1uSizes[1]);
    u(1, 8 * (1uSizes[0] + defaultSeparator), rowIndex * 1uSizes[1]);
    u(1, 9 * (1uSizes[0] + defaultSeparator), rowIndex * 1uSizes[1]);
    
    u(1, 10 * (1uSizes[0] + defaultSeparator), rowIndex * 1uSizes[1]);
    u(1, 11 * (1uSizes[0] + defaultSeparator), rowIndex * 1uSizes[1]);
    u(1, 12 * (1uSizes[0] + defaultSeparator), rowIndex * 1uSizes[1]);
    u(1, 13 * (1uSizes[0] + defaultSeparator), rowIndex * 1uSizes[1]);
}


module row3()
{
    rowIndex = 3;
    offsetX = 1 * (1_5uSizes[0] + defaultSeparator);
    offsetY = rowIndex * 1uSizes[1] + (rowIndex - 2) * defaultSeparator;
    
    u(1.5, 0 * (1uSizes[0] + defaultSeparator), offsetY);
    u(1, offsetX + 0 * (1uSizes[0] + defaultSeparator), offsetY);
    u(1, offsetX + 1 * (1uSizes[0] + defaultSeparator), offsetY);
    u(1, offsetX + 2 * (1uSizes[0] + defaultSeparator), offsetY);
    u(1, offsetX + 3 * (1uSizes[0] + defaultSeparator), offsetY);
    u(1, offsetX + 4 * (1uSizes[0] + defaultSeparator), offsetY);
    
    u(1, offsetX + 5 * (1uSizes[0] + defaultSeparator), offsetY);
    u(1, offsetX + 6 * (1uSizes[0] + defaultSeparator), offsetY);
    u(1, offsetX + 7 * (1uSizes[0] + defaultSeparator), offsetY);
    u(1, offsetX + 8 * (1uSizes[0] + defaultSeparator), offsetY);
    
    u(1, offsetX + 9 * (1uSizes[0] + defaultSeparator), offsetY);
    u(1, offsetX + 10 * (1uSizes[0] + defaultSeparator), offsetY);
    u(1, offsetX + 11 * (1uSizes[0] + defaultSeparator), offsetY);
    u(1, offsetX + 12 * (1uSizes[0] + defaultSeparator), offsetY);
}
    
module row4()
{
    rowIndex = 4;
    offsetX = 1 * (1_75uSizes[0] + defaultSeparator);
    offsetY = rowIndex * 1uSizes[1] + (rowIndex - 2) * defaultSeparator;
    
    u(1.75, 0 * (1uSizes[0] + defaultSeparator), offsetY);
    u(1, offsetX + 0 * (1uSizes[0] + defaultSeparator), offsetY);
    u(1, offsetX + 1 * (1uSizes[0] + defaultSeparator), offsetY);
    u(1, offsetX + 2 * (1uSizes[0] + defaultSeparator), offsetY);
    u(1, offsetX + 3 * (1uSizes[0] + defaultSeparator), offsetY);
    u(1, offsetX + 4 * (1uSizes[0] + defaultSeparator), offsetY);
    
    u(1, offsetX + 5 * (1uSizes[0] + defaultSeparator), offsetY);
    u(1, offsetX + 6 * (1uSizes[0] + defaultSeparator), offsetY);
    u(1, offsetX + 7 * (1uSizes[0] + defaultSeparator), offsetY);
    u(1, offsetX + 8 * (1uSizes[0] + defaultSeparator), offsetY);
    
    u(1, offsetX + 9 * (1uSizes[0] + defaultSeparator), offsetY);
    u(1, offsetX + 10 * (1uSizes[0] + defaultSeparator), offsetY);
    u(1, offsetX + 11 * (1uSizes[0] + defaultSeparator), offsetY);
    u(1, offsetX + 12 * (1uSizes[0] + defaultSeparator), offsetY);
}

module row5()
{
    rowIndex = 5;
    offsetX = 1 * (2_25uSizes[0] + defaultSeparator);
    offsetY = rowIndex * 1uSizes[1] + (rowIndex - 2) * defaultSeparator;
    
    u(2.25, 0 * (1uSizes[0] + defaultSeparator), offsetY);
    u(1, offsetX + 0 * (1uSizes[0] + defaultSeparator), offsetY);
    u(1, offsetX + 1 * (1uSizes[0] + defaultSeparator), offsetY);
    u(1, offsetX + 2 * (1uSizes[0] + defaultSeparator), offsetY);
    u(1, offsetX + 3 * (1uSizes[0] + defaultSeparator), offsetY);
    u(1, offsetX + 4 * (1uSizes[0] + defaultSeparator), offsetY);
    
    u(1, offsetX + 5 * (1uSizes[0] + defaultSeparator), offsetY);
    u(1, offsetX + 6 * (1uSizes[0] + defaultSeparator), offsetY);
    u(1, offsetX + 7 * (1uSizes[0] + defaultSeparator), offsetY);
    u(1, offsetX + 8 * (1uSizes[0] + defaultSeparator), offsetY);
    
    u(1, offsetX + 9 * (1uSizes[0] + defaultSeparator), offsetY);
    u(1, offsetX + 10 * (1uSizes[0] + defaultSeparator), offsetY);
    u(1, offsetX + 11 * (1uSizes[0] + defaultSeparator), offsetY);
    u(1, offsetX + 12 * (1uSizes[0] + defaultSeparator), offsetY);
}

module row6()
{
    rowIndex = 6;
    offsetX = (1_25uSizes[0] + defaultSeparator);
    offsetY = rowIndex * 1uSizes[1] + (rowIndex - 2) * defaultSeparator;
    
    u(1.25, 0 * (1uSizes[0] + defaultSeparator), offsetY);
    u(1.25, 1 * offsetX + 0 * (1uSizes[0] + defaultSeparator), offsetY);
    u(1.25, 2 * offsetX + 1 * (1uSizes[0] + defaultSeparator), offsetY);
    u(1, 2 * offsetX + 2 * (1uSizes[0] + defaultSeparator), offsetY);
    u(1, 2 * offsetX + 3 * (1uSizes[0] + defaultSeparator), offsetY);
    u(1, 2 * offsetX + 4 * (1uSizes[0] + defaultSeparator), offsetY);
    
    u(1, 2 * offsetX + 5 * (1uSizes[0] + defaultSeparator), offsetY);
    u(1, 2 * offsetX + 6 * (1uSizes[0] + defaultSeparator), offsetY);
    u(1, 2 * offsetX + 7 * (1uSizes[0] + defaultSeparator), offsetY);
    u(1, 2 * offsetX + 8 * (1uSizes[0] + defaultSeparator), offsetY);
    
    u(1, 2 * offsetX + 9 * (1uSizes[0] + defaultSeparator), offsetY);
    u(1, 2 * offsetX + 10 * (1uSizes[0] + defaultSeparator), offsetY);
    u(1, 2 * offsetX + 11 * (1uSizes[0] + defaultSeparator), offsetY);
    u(1, 2 * offsetX + 12 * (1uSizes[0] + defaultSeparator), offsetY);
}