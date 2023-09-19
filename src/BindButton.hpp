#ifndef __BINDBUTTON_H
#define __BINDBUTTON_H
#include "BindView.h"
#include "BindUtils.hpp"
// TODO: Extract the class to a serprate .h and .c file! Now!
/**
 * @brief The BindButton class represents a button UI element for use with BindCanvas.
 *
 * BindButton is a class that defines a button UI element that can be used within BindCanvas-based
 * applications. It inherits from the BindView class and provides functionality to create and
 * customize buttons, including setting labels, positions, colors, and sizes.
 *
 * Buttons created with BindButton can be synchronized with BindCanvas through the Bind framework,
 * allowing interactive user interfaces to be built for various applications.
 *
 * @note To use BindButton effectively, you can set the label, position, font size, text color,
 * background color, and other properties to tailor the button's appearance and behavior.
 */
class BindButton : public BindView
{

public:

  /**
   * @brief Constructs a BindButton with a custom label.
   *
   * This constructor creates a BindButton with a custom text label.
   * The label can be used to define the button's text content.
   *
   * @param cstr A pointer to the character array representing the custom label for the button.
   */
  BindButton(const char *cstr)
  {
    setlabel(cstr);
  }

  BindButton()
  {
    setlabel("Button");
  }

  int16_t x;          // X-coordinate position of the button
  int16_t y;          // Y-coordinate position of the button
  uint8_t cmdId = 0;  // Command ID for the button
  int16_t fontSize;   // Font size of the button's label
  int32_t color;      // Text color of the button
  int32_t backColor;  // Background color of the button

  /**
   * @brief Sets the label text for the button.
   *
   * This function allows you to set the text label for the button.
   * @note You need to sync the button, e.g. call bind.sync(bindButton).
   *
   * @param cstr A pointer to the character array representing the label text.
   */
  void setlabel(const char *cstr)
  {
    str = cstr;
  }

  /**
   * @brief Retrieves the bytes representing the button for synchronization.
   *
   * This function is used to gather the bytes that represent the button's properties for synchronization.
   * @note The user does not need to call this function, Bind calls it internally.
   * 
   * @param out A pointer to the output buffer where the button data will be stored.
   * @return The number of bytes written to the output buffer.
   */
  uint16_t getBytes(uint8_t *out) override
  {
    offset = 0;
    strLength = strlen(str);
    if (strLength > MAX_STRING_LENGTH_TERMINAL)
    {
      strLength = MAX_STRING_LENGTH_TERMINAL;
    }
    copyAndOffset(out, &offset, &objID, sizeof(objID));
    copyAndOffset(out, &offset, &x, sizeof(x));
    copyAndOffset(out, &offset, &y, sizeof(y));
    copyAndOffset(out, &offset, &tag, sizeof(tag));
    copyAndOffset(out, &offset, &cmdId, sizeof(cmdId));
    copyAndOffset(out, &offset, &fontSize, sizeof(fontSize));
    copyAndOffset(out, &offset, &color, sizeof(color));
    copyAndOffset(out, &offset, &backColor, sizeof(backColor));
    copyAndOffset(out, &offset, str, strLength);
    return offset;
  }

  private:
  
  uint8_t objID = BindIDs::button;
  uint16_t offset = 0;
  int strLength = 0;
  const char *str;
};
#endif /* __BINDBUTTON_H */