#ifndef _STATE_H_
#define _STATE_H_

void null_func(void);

class State
{
public:
        State(int id, void (*func)(void) = null_func) {
                id_ = id;
                func_ = func;
        }
        State() = default;
        State(State &&) = default;
        State(const State &) = default;
        State &operator=(State &&) = default;
        State &operator=(const State &) = default;
        ~State() { }

        int get_ID() const { return id_; }
        void call_StateFunc() const { func_(); }

private:
        int id_;
        void (*func_)(void);
};

#endif // !_STATE_H_
