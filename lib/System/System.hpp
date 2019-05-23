namespace System{
    enum Status{
        Idle,
        Watch,
        TargetLocking,
        Fire,
        Service
    };
    const int pinSwitch = 11;
    extern Status machineState;
}