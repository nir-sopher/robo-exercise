import brain
import time
import sys

def main():
    if not brain.init():
        print("Failed to init brain module", sys.stderr)
        return -1


    theBrain = brain.Brain();
    if not theBrain.initPosition(1.2):
        print("Failed to init position", sys.stderr)
        return -1

    numMotors = 10
    for motor in range(numMotors):
        if not theBrain.initAddMotor(str(motor), motor):
            print("Failed to init motor", sys.stderr)
            return -1
        
    if not theBrain.initNetFunction("mul"):
        print("Failed to brain net function", sys.stderr)
        return -1

    if not theBrain.initDone():
        print("Failed to init brain", sys.stderr)
        return -1

    if not theBrain.launch():
        print("Failed to launch brain", sys.stderr)
        return -1

    time.sleep(3)

    theBrain.terminate()

    return 0

if __name__ == "__main__":
    sys.exit(main())
