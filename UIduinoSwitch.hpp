#ifndef __UIDUINOSWITCH_H
#define __UIDUINOSWITCH_H
class Switch {
  private:
    bool * value = NULL;
  public:
    Switch() {
      Switch(NULL);
    }
    Switch(bool *val) {
      value = val;
    }
    void update(bool val) {
      if (value != NULL) {
        *value = val;
      }
    }
};
#endif /* __UIDUINOSWITCH_H */
