/**
 * Represents time - hours:minutes.
 * @author Ofir Rozanes
 * @version 26.04.2020
 */
public class Time1 {
    private int _hour;
    private int _minute;
    private final int DEFAULT = 0;
    private final int FULL_DAY= 23;
    private final int MIN_IN_HOUR= 59;
    private final int FULL_HOUR = 60;

    /**
     * Constructs a Time1 object.
     * Construct a new time body with the specified hour and minute.
     * hour should be between 0-23, otherwise it should be set to 0.
     * minute should be between 0-59, otherwise it should be set to 0.
     * @param hour the hour of the time
     * @param minute the minute of the time
     */
    //Constructors.
    public Time1 (int hour, int minute) {
        _hour=hour;
        _minute=minute;

        if (hour>FULL_DAY||hour<DEFAULT)//Checks if time is legal.
            _hour = DEFAULT;
        if (minute>MIN_IN_HOUR||minute<DEFAULT)
            _minute = DEFAULT;
    }

    /**
     * Copy constructor for Time1.
     * Construct a time with the same instance variables as another time.
     * @param other The time object from which to construct the new time
     */
    public Time1 (Time1 other){
        this._hour = other._hour;
        this._minute = other._minute;
    }
    //Getters.
    /**
     * Returns the hour of the time.
     * @return The hour of the time
     */
    public int getHour(){
        return _hour;
    }

    /**
     * Returns the minutes of the time.
     * @return The minutes of the time.
     */
    public int getMinute(){
        return _minute;
    }
    //Setters.
    /**
     * Changes the hour of the time. If an illegal number is received hour will be unchanged.
     * @param newHour The new hour.
     */
    public void setHour (int newHour){
        if (newHour>=DEFAULT&&newHour<=FULL_DAY)
            _hour = newHour;
    }

    /**
     * Changes the minute of the time. If an illegal number is received minute will be unchanged.
     * @param newMinute The new minute.
     */
    public void setMinute(int newMinute){
        if (newMinute>=DEFAULT&&newMinute<=MIN_IN_HOUR)
            _minute = newMinute;
    }

    /**
     * Returns a string representation of this time ("hh:mm").
     * @return String representation of this time ("hh:mm").
     */
    public String toString(){
        String hour =""+ _hour;
        String minute =""+ _minute;
        if (_hour<10&&_hour>=0)//Adding zero to the time.
            hour = "0" + _hour;
        if (_minute<10&&_minute>=0)
            minute = "0" + _minute;
        return hour + ":" + minute;
    }

    /**
     * Return the amount of minutes since midnight.
     * @return amount of minutes since midnight.
     */
    public int minFromMidnight(){
        int minFromMidnight;
        minFromMidnight = (_hour*FULL_HOUR) + _minute;
        return minFromMidnight;
    }

    /**
     * Checks if the received time is equal to this time.
     * @param other The time to be compared with this time.
     * @return true if the received time is equal to this time.
     */
    public boolean equals (Time1 other){
        return this._hour==other._hour && this._minute==other._minute;
    }

    /**
     * Checks if this time is before a received time.
     * @param other The time to check if this time is before
     * @return true if this time is before other time
     */
    public boolean before (Time1 other){
        if (this._hour<other._hour)
            return true;
        if (this._hour==other._hour)
            if (this._minute < other._minute)
                return true;
            else
                return false;
        return false;
    }

    /**
     * Check if this time is after a received time.
     * @param other The time to check if this time is after
     * @return true if this time is after other time
     */
    public boolean after (Time1 other){
        return other.before(this);//if other before this, this after other.
    }

    /**
     * Calculates the difference (in minutes) between two times. Assumption: this time is after other time.
     * @param other The time to check the difference to.
     * @return int difference in minutes.
     */
    public int difference (Time1 other){
        int difference;
        difference = Math.abs(((this._hour-other._hour)*FULL_HOUR)+(this._minute-other._minute));
        return difference;
    }

    /**
     * Adds num Minutes to time.
     * @param num The number of minutes to add.
     * @return the update time.
     */
    public Time1 addMinutes(int num){
        int hours = (num/FULL_HOUR);
        int min = (num%FULL_HOUR);
        _hour += hours;
        _minute += min;
        if (_minute>=FULL_HOUR)
            ++ _hour;
        _minute=_minute%FULL_HOUR;
        _hour=_hour%24;
        if (_minute<0){
            _minute = FULL_HOUR + _minute;
            -- _hour;}
        return new Time1(_hour,_minute);
    }
}
