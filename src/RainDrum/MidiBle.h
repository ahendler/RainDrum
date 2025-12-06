#pragma once

class MidiBle {
    public:
        static int noteToPlay; // 0 to 7
        MidiBle();
        void initialize();
        void read();
    private:
        static int getNotePosition(int note);
};