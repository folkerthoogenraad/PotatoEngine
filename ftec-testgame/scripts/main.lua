
i = 0;

function update()
  --currently unused function, but very useful for drawing stuff
  i = i + 1;
  if(i > 60) then
    print("Width ", window_get_width());
    print("Height ", window_get_height());
    i = 0;
  end

end
