/*
 * Author: YOAN BERNATCHEZ
 * Contact: yoan_bernatchez@hotmail.com
 * Date: 2020-02-05
 * Project: Tower Defense
 * File: THudCompHelper.h
 *
 * Brief: Contains helper template functions mainly for HUD and HUD components.
 */

#ifndef THUDCOMPHELPER_H_INCLUDED
#define THUDCOMPHELPER_H_INCLUDED

#include <vector>
#include <string>

namespace HudCompHelper
{
    /**
     * @brief Removes a component at the specified index from a vector.
     *
     * @param vec:   Vector to objects or base types. This should be a vector
     *               to a child class of HudComponent, but could be any other
     *               vector as well.
     * @param index: Index of the basetype/object to remove from the vector.
     */
    template <class T>
    static void RemoveComponentAtIndex(std::vector<T> &vec, unsigned int index)
    {
        if(index < vec.size())
        {
            vec.erase(vec.begin() + index);
        }
    }

    /**
     * @brief Removes components matching a label from a vector of any
     *        HudComponent child class.
     *
     * @param vec:   Vector to a HudComponent child class.
     *               If the type isn't a HudComponent child class with a
     *               GetLabel() function member, then calling this function
     *               gives compilation build errors (does not compile).
     * @param label: String label used to identify a component.
     */
    /* [Deprecated]
    template <class T>
    static void RemoveComponentByLabel(std::vector<T> &vec,
                                       std::string label)
    {
        int j = 0;

        for(auto &i : vec)
        {
            if(i.GetLabel().compare(label) == 0)
            {
                vec.erase(vec.begin() + j);
            }
            j++;
        }
    }
    */
}

#endif // THUDCOMPHELPER_H_INCLUDED
