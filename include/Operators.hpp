#ifndef OPERATORS_HPP__
#define OPERATORS_HPP__

#include "DiscConfig.hpp"
#include "GridData.hpp"


template<typename T = double>
class Operators {
public:
    const DiscConfig<T> *discConfig;

    /*
     * Default constructor doing nothing
     */
    Operators() :
            discConfig(nullptr) {
    }

    /*
     * Setup constructor
     */
    Operators(const DiscConfig<T> &i_discConfig) {
        setup(i_discConfig);
    }

    void setup(const DiscConfig<T> &i_discConfig) {
        discConfig = &i_discConfig;
    }


    /*
     * Approximate
     *  * first derivative with
     *  * second order centered finite difference
     */
    GridData<T> diff1(const GridData<T> &i_d) const {
        GridData<T> o;
        o.setup_like(i_d);

        for (std::size_t i = 1; i < o.size - 1; i++) {
            o.data[i] = (i_d.data[i + 1] - i_d.data[i - 1]) * 0.5 * discConfig->inv_dx;
        }

        // periodic boundaries
        o.data[0] = (i_d.data[1] - i_d.data[o.size - 1]) * 0.5 * discConfig->inv_dx;
        o.data[o.size - 1] = (i_d.data[0] - i_d.data[o.size - 2]) * 0.5 * discConfig->inv_dx;

        //o.set_zero();
        return o;
    }

    GridData<T> diff1_staggered_h(const GridData<T> &i_v) const {
        GridData<T> o;
        o.setup_like(i_v);
        
        for (std::size_t i = 0; i < o.size; i++) {
            std::size_t i_prev = (i == 0) ? (o.size - 1) : (i - 1);
            o.data[i] = (i_v.data[i] - i_v.data[i_prev]) * discConfig->inv_dx;
        }
        
        return o;
    }

    GridData<T> diff1_staggered_v(const GridData<T> &i_h) const {
        GridData<T> o;
        o.setup_like(i_h);
        
        for (std::size_t i = 0; i < o.size; i++) {
            std::size_t i_next = (i + 1) % o.size;
            o.data[i] = (i_h.data[i_next] - i_h.data[i]) * discConfig->inv_dx;
        }
        
        return o;
}
};

#endif
