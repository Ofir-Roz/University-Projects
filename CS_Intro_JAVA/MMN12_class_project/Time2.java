/**
 * Time2 - Represents time by the minutes from midnight. Values must represent a proper time.
 * @author Ofir Rozanes.
 * @version 29.4.2020.
 */
public class Time2 {
    private int _minFromMid;
    private final int DEFAULT = 0;
    private final int HOUR = 59;
    private final int DAY = 23;
    private final int FULL_HOUR = 60;
    private final int MIN_IN_A_DAY = 1440;

    //Constructors.
    /**
     * Constructs a Time2 object.
     * Construct a new time body with the specified hour and minute.
     * hour should be between 0-23, otherwise it should be set to 0.
     * minute should be between 0-59, otherwise it should be set to 0.
     * @param h the hour of the time
     * @param m the minute of the time
     */
    public Time2 (int h, int m){
        if (h < DEFAULT || h > DAY)
            h = DEFAULT;
        if (m < DEFAULT || m > HOUR)
            m = DEFAULT;
        _minFromMid = h * FULL_HOUR + m;
    }

    /**
     * Copy constructor for Time2. Constructs a time with the same variables as another time.
     * @param other The time object from which to construct the new time.
     */
    public Time2 (Time2 other){
        _minFromMid=other._minFromMid;
    }

    //getters.
    /**
     *Returns the hour of the time.
     * @return The hour of the time.
     */
    public int getHour(){
        return _minFromMid/FULL_HOUR;
    }

    /**
     * Returns the minute of the time.
     * @return The minute of the time.
     */
    public int getMinute(){
        return _minFromMid%FULL_HOUR;
    }

    //Setters.
    /**
     * Changes the hour of the time. If an illegal number is received, hour will remain unchanged.
     * @param num The new hour.
     */
    public void setHour(int num){
        int hourToAdd;//we need to remember to change only the hours of the hour.
        if (num>=DEFAULT&&num<=DAY) {
            hourToAdd = num * FULL_HOUR;
            _minFromMid = (_minFromMid%FULL_HOUR) + hourToAdd;}
    }

    /**
     * Changes the minute of the time. If an illegal number is received minute will remain unchanged.
     * @param num The new minute.
     */
    public void setMinute(int num) {
        int minToAdd;//we need to remember not to lose the hours of the original hour.
        if (num >= DEFAULT && num <= HOUR) {
            minToAdd = num;
            _minFromMid = (_minFromMid+minToAdd)-(_minFromMid%FULL_HOUR);
        }
    }

    /**
     * Return the amount of minutes since midnight.
     * @return amount of minutes since midnight.
     */
    public int minFromMidnight(){
        return _minFromMid;
    }

    /**
     * Checks if the received time is equal to this time.
     * @param other The time to be compared with this time.
     * @return True if the received time is equal to this time.
     */
    public boolean equals(Time2 other){
        return _minFromMid==other._minFromMid;
    }

    /**
     * Checks if this time is before a received time.
     * @param other The time to check if this time is before.
     * @return True if this time is before other time.
     */
    public boolean before(Time2 other){
        return _minFromMid<other._minFromMid;
    }

    /**
     * Checks if this time is after a received time.
     * @param other The time to check if this time is after.
     * @return True if this time is after other time.
     */
    public boolean after(Time2 other){
        return other.before(this);
    }

    /**
     * Calculates the difference (in minutes) between two times.
     * @param other The time to check the difference with. Assumption: this time is after other time
     * @return int difference in minutes.
     */
    public int difference(Time2 other){
        int difference;
        difference = Math.abs(_minFromMid-other._minFromMid);
        return difference;
    }

    /**
     * Returns a string representation of this time(hh:mm).
     * @return String representation of this time(hh:mm).
     */
    public String toString(){
        int hours = _minFromMid/FULL_HOUR;
        int min = _minFromMid%FULL_HOUR;
        String time ="";
        if (hours<10)
            time += "0";
        time += hours + ":";
        if (min<10)
            time += "0";
        time += min;
        return time;
    }

    /**
     * Adds num Minutes to time.
     * @param num The number of minutes to add.
     * @return the update time.
     */
    public Time2 addMinutes(int num){
        _minFromMid += num;
        _minFromMid = _minFromMid%MIN_IN_A_DAY; //for a legal time.
        int h = _minFromMid/FULL_HOUR;
        int m = _minFromMid%FULL_HOUR;
        Time2 newTime = new Time2(h,m);
        return newTime;
    }
}
