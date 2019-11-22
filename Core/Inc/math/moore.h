#ifndef _MOORE_H_
#define _MOORE_H_

#include "state.h"
#include "array.h"

template <size_t N_States, size_t N_Inputs>
class Moore_Machine
{
public:
        Moore_Machine(State* (&st)[N_States],
                      int (&in)[N_Inputs],
                      size_t (&d)[N_States][N_Inputs]) {

                              arrCopy(states_, st);
                              arrCopy(inputs_, in);
                              arrCopy(del_, d);

                              curr_state_ = states_[0];

                      }
        Moore_Machine() = default;
        Moore_Machine(Moore_Machine &&) = default;
        Moore_Machine(const Moore_Machine &) = default;
        Moore_Machine &operator=(Moore_Machine &&) = default;
        Moore_Machine &operator=(const Moore_Machine &) = default;
        ~Moore_Machine() { }

        int feed(int input) {
                int st_index = arrIndex(states_, curr_state_);
                if (st_index == -1) {
                        return -1;
                }

                int in_index = arrIndex(inputs_, input);
                if (in_index == -1) {
                        return -1;
                }

                // The state transition table gives the index of the new state.
                // d : S x I -> S
                curr_state_ = states_[del_[st_index][in_index]];
                // For a moore machine the output function is called for each state.
                curr_state_->call_StateFunc();

                return curr_state_->get_ID();
        }

private:
        State* states_[N_States];
        int inputs_[N_Inputs];
        size_t del_[N_States][N_Inputs];

        State* curr_state_;
};

#endif // !_MOORE_H_
