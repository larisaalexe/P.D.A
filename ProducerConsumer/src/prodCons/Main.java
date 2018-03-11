package prodCons;

import java.util.LinkedList;
import java.util.Queue;
import java.util.concurrent.Semaphore;

public class Main {
	private static final int N = 2;

	public static void main(String args[]){
		
		Queue<Integer> queue = new LinkedList<>();
		int queueSize = 5;
		Semaphore semFree = new Semaphore(N);
		Semaphore semFull = new Semaphore(0);
		Producer prod = new Producer(queue,queueSize, semFree, semFull);
		Consumer cons = new Consumer(queue,queueSize, semFree, semFull);
		
		prod.start();
		cons.start();
	}
}
