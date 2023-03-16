  // This is the command sequence that rotates the driver coordinate frame
  // The  A0039793 Hardware can only support Inverted Portrait? But not implemented yet!

  rotation = m % 4;
  switch (rotation) {
    case 0: // Portrait (default after Init)
      _width  = _init_width;
      _height = _init_height;
      break;

    case 1: // Landscape (Portrait + 90)
      _width  = _init_height;
      _height = _init_width;
      break;

    case 2: // Inverted portrait
      _width  = _init_width;
      _height = _init_height;
       break;

    case 3: // Inverted landscape
      _width  = _init_height;
      _height = _init_width;
      break;
  }
