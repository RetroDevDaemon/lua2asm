byte x 
 byte y 
  ram word z 
    word f; word g;
function init(int k)
{   -- ignored after function init
    for f=0,10 { -- { is 'do' if on a for line
       z = x + y 
    } --end
    return z -- return type gathered from end statement
} --end