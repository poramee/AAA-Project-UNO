namespace System{
    enum class Status{
        Idle,
        Watch,
        TargetLocking,
        Fire,
        Reload
    };
    extern Status machineState;
}