#ifndef TIMER_H
#define TIMER_H

#include <boost/date_time.hpp>
/*!
 *  \addtogroup Utilities
 *  @{
 */

/*!
 * \brief Provides a stopwatch mechanism 
 *
 * Designed to measure the amount of time elapsed from a particular time when activated to when is deactivated.
 *
 * \note timer class requires boost_date_time library
 * 
 * quick demo:
 * \include cf-util/timer_demo.cpp
 */
class timer
{
public:
	/*!
	 * \brief Initializes a new instance of the timer class, and sets all the properties to their initial values.
	 *
	 * \n FullName:  timer::timer
	 * \n Access:    public  
	 */
	timer();
	/*!
	 * \brief restarts a timer
	 *
	 * Resets the stopwatch to zero.
	 *
	 * \n FullName:  timer::restart
	 * \n Access:    public  
	 *
	 * \return void
	 *
	 */
	void restart();
	/*!
	 * \brief returns elapsed time
	 *
	 * returns elapsed time from timer creation or restart()
	 *
	 * \n FullName:  timer::elapsed
	 * \n Access:    public  
	 *
	 * \return boost::posix_time::time_duration
	 * \note you can use std::cout with this function
	 * \code
	 * timer t;
	 * std::cout << "time passed: " << t.elapsed() << std::endl ;
	 * \endcode
	 *
	 */
	boost::posix_time::time_duration elapsed() const;
private:
	boost::posix_time::ptime start_time;
};
/*! @} */
#endif // TIMER_H
