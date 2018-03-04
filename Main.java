#Producer Consumer
package prodCons;

import java.util.LinkedList;
import java.util.Queue;

public class Main {
	public static void main(String args[]){
		
		Queue<Integer> queue = new LinkedList<>();
		int queueSize = 5; 
		Producer prod = new Producer(queue,queueSize);
		Consumer cons = new Consumer(queue,queueSize);
		
		prod.start();
		cons.start();
	}
}
