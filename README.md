# NextionDisplay Library
A library to interface from the onethinx module to a nextion display

## Feature requests and issues
You can create a feature or issue request on the issues tab
this might take "longer" to resolve

If you want your feature / issue request resolved qickly you can email me at:
jellemh@gmail.com

## Example code
The configuration structure:
```C
const NextionConfig nextionConfig =
{
	.base = UART_HW,
};
```

`UART_HW` is defined in the device configurator

Functions:
* Set the text in a text-box
  ```c
  Nextion_SetText(nextionConfig, "text-box", "Hello World!");
  ```
  `"text-box"` the name of the element.
  
  `"Hello World!"` the new text for the text-box
  
* Set the progress of a progress-bar
  ```c
  Nextion_SetProgressbar(nextionConfig, "progress-bar", "50");
  ```
  `"progress-bar"` the name of the element.
  
  `"50"` the value to set the progress bar to
  
* Change the page on the display
  ```c
  Nextion_ChangePage(nextionConfig, "next-page");
  ```
  `"next-page"` the name of the page you want to change to
  
* Read data send from the display
  ```c
  char buffer[64];
  if (Nextion_Read(nextionConfig, buffer, 64)) {
    // Code to execute when the data is read
  }
  ```
  `buffer` the buffer the data is read to
  
  `64` the length of the buffer
  
