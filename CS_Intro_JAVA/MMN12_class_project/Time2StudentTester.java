public class Time2StudentTester
{
    public static void main(String [] args) {
        
        System.out.println("\n********** Test Time2 - Started **********\n");
        System.out.println("\n1. Testing Constructors and toString:");
        Time2 t1 = new Time2(17, 45);
        System.out.println("\tt1=" + t1);
        Time2 t2 = new Time2(t1);
        System.out.println("\tt2=" + t2);
        
        System.out.println("\n2. Testing accessors and mutators:");
        t1.setHour(20);
        t1.setMinute(10);
        System.out.println("\tt1=" + t1);
        System.out.println("\tHour   of t1=" + t1.getHour());
        System.out.println("\tMinute of t1=" + t1.getMinute());
        System.out.println("\n2. Testing accessors and mutators 2:");
        t1.setHour(27);
        t1.setMinute(59);
        System.out.println("\tt1=" + t1);
        System.out.println("\tHour   of t1=" + t1.getHour());
        System.out.println("\tMinute of t1=" + t1.getMinute());
        
        System.out.println("\n3. Testing minFromMidnight method:");
        t1 = new Time2(10, 15);
        System.out.println("\tt1=" + t1);
        System.out.println("\tMinutes from midnight of t1=" + t1.minFromMidnight());
        System.out.println("\n3. Testing minFromMidnight method 2:");
        t1 = new Time2(00, 15);
        System.out.println("\tt1=" + t1);
        System.out.println("\tMinutes from midnight of t1=" + t1.minFromMidnight());
        System.out.println("\n3. Testing minFromMidnight method 3:");
        t1 = new Time2(23, 59);
        System.out.println("\tt1=" + t1);
        System.out.println("\tMinutes from midnight of t1=" + t1.minFromMidnight());
       
        System.out.println("\n4. Testing equals method:");
        Time2 t3=new Time2(12, 34);
        Time2 t4=new Time2(23, 45);
        System.out.println("\tt3=" + t3);
        System.out.println("\tt4=" + t4);
        if(t3.equals(t4))
             System.out.println("\tt3 is the same time as t4");
        else 
             System.out.println("\tt3 isn't the same time as t4");
        System.out.println("\n4. Testing equals method 2:");
        Time2 t5=new Time2(11, 20);
        Time2 t6=new Time2(11, 20);
        System.out.println("\tt3=" + t5);
        System.out.println("\tt4=" + t6);
        if(t5.equals(t6))
             System.out.println("\tt5 is the same time as t6");
        else 
             System.out.println("\tt5 isn't the same time as t6");
             
        System.out.println("\n5. Testing before method:");
        if(t3.before(t4))
             System.out.println("\tt3 is before t4");        
        else 
             System.out.println("\tt3 isn't before t1");
        System.out.println("\n5. Testing before method 2:");
        if(t5.before(t6))
             System.out.println("\tt5 is before t6");        
        else 
             System.out.println("\tt5 isn't before t6");     
             
        System.out.println("\n6. Testing after method:");
        if(t4.after(t3))
             System.out.println("\tt4 is after t3");
        else 
             System.out.println("\tt4 isn't after t3");
        System.out.println("\n6. Testing after method:");
        if(t5.after(t6))
             System.out.println("\tt5 is after t6");
        else 
             System.out.println("\tt6 isn't after t5");     
             
        System.out.println("\n7. Testing difference method:");
        t1=new Time2(11, 25);
        t2=new Time2(10, 15);
        System.out.println("\tt1=" + t1);
        System.out.println("\tt2=" + t2);
        System.out.println("\tThe difference in minutes between times t1 and t2 is : "+t1.difference(t2));
        System.out.println("\n7. Testing difference method 2:");
        t1=new Time2(11, 25);
        t2=new Time2(11, 25);
        System.out.println("\tt1=" + t1);
        System.out.println("\tt2=" + t2);
        System.out.println("\tThe difference in minutes between times t1 and t2 is : "+t1.difference(t2));
        System.out.println("\n7. Testing difference method 3:");
        t1=new Time2(11, 25);
        t2=new Time2(01, 00);
        System.out.println("\tt1=" + t1);
        System.out.println("\tt2=" + t2);
        System.out.println("\tThe difference in minutes between times t1 and t2 is : "+t1.difference(t2));
        
        System.out.println("\n8. Testing addMinutes method:");
        System.out.println("\tt1=" + t1);
        System.out.println("\tAdding 10 minutes to t1="+t1.addMinutes(10));
        System.out.println("\n8. Testing addMinutes method 2:");
        System.out.println("\tt1=" + t1);
        System.out.println("\tAdding 80 minutes to t1="+t1.addMinutes(80));
        System.out.println("\n8. Testing addMinutes method 3:");
        System.out.println("\tt1=" + t1);
        System.out.println("\tAdding -40 minutes to t1="+t1.addMinutes(-40));
        System.out.println("\n8. Testing addMinutes method:");
        System.out.println("\tt1=" + t1);
        System.out.println("\tAdding -80 minutes to t1="+t1.addMinutes(-80));
        
        System.out.println("\n********** Test Time2 - Finished **********\n");
    
    }
}
