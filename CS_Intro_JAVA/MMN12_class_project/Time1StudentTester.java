public class Time1StudentTester
{
    public static void main(String [] args) {

        System.out.println("\n********** Test Time1 - Started **********\n");
        System.out.println("\n1. Testing Constructors and toString:");
        Time1 t1 = new Time1(17, 45);
        System.out.println("\tt1=" + t1);
        Time1 t2 = new Time1(t1);
        System.out.println("\tt2=" + t2);

        System.out.println("\n2. Testing accessors and mutators:");
        t1.setHour(20);
        t1.setMinute(10);
        System.out.println("\tt1=" + t1);
        System.out.println("\tHour   of t1=" + t1.getHour());
        System.out.println("\tMinute of t1=" + t1.getMinute());

        System.out.println("\n3. Testing minFromMidnight method:");
        t1 = new Time1(10, 15);
        System.out.println("\tt1=" + t1);
        System.out.println("\tMinutes from midnight of t1=" + t1.minFromMidnight());
        System.out.println("\n3. Testing minFromMidnight method.2:");
        t1 = new Time1(00, 03);
        System.out.println("\tt1=" + t1);
        System.out.println("\tMinutes from midnight of t1=" + t1.minFromMidnight());
        System.out.println("\n3. Testing minFromMidnight method:");
        t1 = new Time1(20, 40);
        System.out.println("\tt1=" + t1);
        System.out.println("\tMinutes from midnight of t1=" + t1.minFromMidnight());

        System.out.println("\n4. Testing equals method:");
        Time1 t3=new Time1(12, 34);
        Time1 t4=new Time1(23, 45);
        System.out.println("\tt3=" + t3);
        System.out.println("\tt4=" + t4);
        if(t3.equals(t4))
            System.out.println("\tt3 is the same time as t4");
        else 
            System.out.println("\tt3 isn't the same time as t4");
        System.out.println("\n4. Testing equals method.2:");
        Time1 t5=new Time1(12, 34);
        Time1 t6=new Time1(12, 34);
        System.out.println("\tt5=" + t5);
        System.out.println("\tt6=" + t6);
        if(t5.equals(t6))
            System.out.println("\tt5 is the same time as t6");
        else 
            System.out.println("\tt5 isn't the same time as t6");     

        System.out.println("\n5. Testing before method:");
        if(t3.before(t4))
            System.out.println("\tt3 is before t4");        
        else 
            System.out.println("\tt3 isn't before t1");  
        System.out.println("\n5. Testing before method.2:");
        if(t5.before(t6))
            System.out.println("\tt5 is before t6");        
        else 
            System.out.println("\tt5 isn't before t6");

        System.out.println("\n6. Testing after method:");
        if(t4.after(t3))
            System.out.println("\tt4 is after t3");
        else 
            System.out.println("\tt4 isn't after t3");  
        System.out.println("\n6. Testing after method.2:");
        if(t6.after(t5))
            System.out.println("\tt4 is after t3");
        else 
            System.out.println("\tt6 isn't after t5");      

        System.out.println("\n7. Testing difference method:");
        t1=new Time1(11, 25);
        t2=new Time1(10, 15);
        System.out.println("\tt1=" + t1);
        System.out.println("\tt2=" + t2);
        System.out.println("\tThe difference in minutes between times t1 and t2 is : "+t1.difference(t2));
        System.out.println("\n7. Testing difference method.2:");
        t1=new Time1(11, 25);
        t2=new Time1(11, 26);
        System.out.println("\tt1=" + t1);
        System.out.println("\tt2=" + t2);
        System.out.println("\tThe difference in minutes between times t1 and t2 is : "+t1.difference(t2));
        t1=new Time1(11, 25);
        t2=new Time1(11, 15);
        System.out.println("\tt1=" + t1);
        System.out.println("\tt2=" + t2);
        System.out.println("\tThe difference in minutes between times t1 and t2 is : "+t1.difference(t2));

        System.out.println("\n8. Testing addMinutes method:");
        System.out.println("\tt1=" + t1);
        System.out.println("\tAdding 10 minutes to t1="+t1.addMinutes(10));
        System.out.println("\tAdding 60 minutes to t1="+t1.addMinutes(60));
        System.out.println("\tAdding -30 minutes to t1="+t1.addMinutes(-30));
        System.out.println("\tAdding 75 minutes to t1="+t1.addMinutes(75));
        System.out.println("\tAdding -75 minutes to t1="+t1.addMinutes(-75));
        System.out.println("\tAdding -30 minutes to t1="+t1.addMinutes(-30));
        System.out.println("\tAdding -40 minutes to t1="+t1.addMinutes(-40));
        Time1 t7=new Time1(21, 45);
        System.out.println("\tt7=" + t7);
        System.out.println("\tAdding 3500 minutes to t7="+t7.addMinutes(3500));
        t7 = new Time1(21, 45);
        System.out.println("\tAdding -1500 minutes to t7="+t7.addMinutes(-1500));
         t7 = new Time1(21, 45);
        System.out.println("\tAdding -3500 minutes to t7="+t7.addMinutes(-3500));
         t7 = new Time1(21, 45);
        System.out.println("\tAdding 1440 minutes to t7="+t7.addMinutes(1440));
        

        System.out.println("\n********** Test Time1 - Finished **********\n");

    }
}
