/**
 * class Train - represents a Train.
 * @author Ofir Rozanes.
 * @version 30.4.2020.
 */
public class Train {
    private String _destination;
    private final Time1 _departure;
    private int _duration;
    private int _passengers;
    private int _seats;
    private int _price;
    private final int DEFAULT = 0;

    //Constructors.
    /**
     * Constructor of class Train.
     * Constructs a new train.
     * Duration should be positive, otherwise it should be set to 0.
     * Pass should be positive, otherwise it should be set to 0.
     * Pass should be less than seats otherwise it should be set to seats.
     * Seats should be positive, otherwise it should be set to 0.
     * Price should be positive, otherwise it should be set to 0.
     * @param destination the destination of the train
     * @param departureH the hour of departure.
     * @param departureM the minute of departure.
     * @param duration the duration of the travel in minutes.
     * @param passengers the number of passengers.
     * @param seats the number of seats in the train.
     * @param price the price of the travel.
     */
    public Train (String destination, int departureH, int departureM, int duration,
                  int passengers, int seats, int price)
    {
        _destination = destination;
        _duration = duration;
        _passengers = passengers;
        _seats = seats;
        _price = price;
        _departure = new Time1(departureH,departureM);//new time object.
        if (passengers<DEFAULT)
            _passengers = DEFAULT;
        if (seats<DEFAULT)
            _seats = DEFAULT;
        if (passengers>seats)
            _passengers = _seats;    
        if (duration<DEFAULT)
            _duration = DEFAULT;
        if (price<DEFAULT)
            _price = DEFAULT;
    }

    /**
     * Copy constructor for Train.
     * Construct a train with the same instance variables as another train.
     * @param other The train object from which to construct the new train.
     */
    public Train (Train other){
        _destination = other._destination;
        _duration = other._duration;
        _passengers = other._passengers;
        _seats = other._seats;
        _price = other._price;
        _departure = new Time1(other._departure);
    }

    /**
     * returns the departure time.
     * @return the departure time.
     */
    public Time1 getDeparture(){
        return new Time1(_departure);
    }

    /**
     * returns the destination.
     * @return the destination of the train.
     */
    public String getDestination(){
        return _destination;
    }

    /**
     * returns the duration of the train.
     * @return the duration of the train.
     */
    public int getDuration(){
        return _duration;
    }

    /**
     * returns the number of passengers.
     * @return the number of passengers.
     */
    public int getPassengers(){
        return _passengers;
    }

    /**
     * returns the price of the train.
     * @return the price of the train.
     */
    public int getPrice(){
        return _price;
    }

    /**
     * returns the number of seats.
     * @return the number of seats.
     */
    public int getSeats(){
        return _seats;
    }
    //Setters.
    /**
     * updates the destination of the train. d in not null.
     * @param d the new destination of the train.
     */
    public void setDestination (String d){
        _destination = d;
    }

    /**
     * updates the duration of the train. d should be positive or zero, otherwise duration is unchanged.
     * @param d the new duration of the train.
     */
    public void setDuration(int d){
        if (d>=DEFAULT)
            _duration = d;
    }

    /**
     * updates the number of passengers. p should be positive or zero, otherwise passengers is unchanged.
     * p should be less than seats otherwise it should be set to seats.
     * @param p the new number of passengers.
     */
    public void setPassengers(int p){
        if (p>=DEFAULT)
            _passengers = p;
        if (p>_seats)
            _passengers = _seats;
    }

    /**
     * updates the price. p should be positive or zero, otherwise price is unchanged.
     * @param p the new price.
     */
    public void setPrice(int p){
        if (p>=DEFAULT)
            _price = p;
    }

    /**
     * updates the number of seats. s should be positive or zero, otherwise seats is unchanged.
     * s should be larger than passengers, otherwise seats is unchanged.
     * @param s the new number of seats.
     */
    public void setSeats(int s){
        if (s>=DEFAULT){
            if (s>=_passengers)
                _seats = s;
        }
    }

    /**
     * updates the departure time of the train. t in not null.
     * @param t the new departure time of the train.
     */
    public void setDeparture(Time1 t){
        _departure.setHour(t.getHour());
        _departure.setMinute(t.getMinute());
    }

    /**
     * Check if the received train is equal to this train.
     * @param other The train to be compared with this train.
     * @return True if the received train is equal to this train.
     */
    public boolean equals(Train other){
        return _destination.equals(other._destination)&&_seats==other._seats&&_departure.equals(other._departure);
    }

    /**
     * Returns the arrival time.
     * @return the arrival time.
     */
    public Time1 getArrivalTime(){
        _departure.addMinutes(_duration);
        return _departure;//+ the time that added.
    }

    /**
     * Add num passengers to the train.
     * @param num The number of passengers to add.
     * @return True if the total number of current passengers and num is less or equal to seats.
     */
    public boolean addPassengers(int num){
        if (_seats>=_passengers+num) {
            _passengers += num;
            return true;
        }
        else
            return false;
    }

    /**
     * Returns true if train is full.
     * @return true if train is full.
     */
    public boolean isFull(){
        return _seats==_passengers;
    }

    /**
     * Returns true if the price for this train is cheaper than the other train. other is not null.
     * @param other the other train to compare price with.
     * @return true if the price for this train is cheaper than the other train.
     */
    public boolean isCheaper(Train other){
        if (this._price<other._price)
            return true;
        else
            return false;
    }

    /**
     * Returns the total price for all passengers.
     * @return the total price for all passengers.
     */
    public int totalPrice(){
        return _price*_passengers;
    }

    /**
     * Returns true if the arrival time of this train is earlier than the arrival time of the other train. other is not null.
     * @param other the other train to compare arrival time with.
     * @return true if the arrival time of this train is earlier than arrival time of the other train.
     */
    public boolean arrivesEarlier(Train other){
        if ((this.getArrivalTime()).before(other.getArrivalTime())) //We use 'before' from Time1 class.
            return true;
        else
            return false;
    }

    /**
     * Return a string representation of the train.
     * @return String representation of the train.
     */
    public String toString(){
        String str ="Train to ";
        str += _destination + " departs at " + _departure.toString();
        if (_passengers==_seats)
            str += ". Train is full.";
        else
            str += ". Train is not full.";
        return str;
    }
}

