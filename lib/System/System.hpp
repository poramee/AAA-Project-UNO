namespace System{
    enum Status{
        Idle,
        Watch,
        TargetLocking,
        Fire,
        Service
    };
    extern Status machineState;
}