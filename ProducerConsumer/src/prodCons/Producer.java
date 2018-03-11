package prodCons;

import java.util.Queue;
import java.util.concurrent.Semaphore;

public class Producer extends Thread {

	private Queue<Integer> queue;
	int queueDimension;
	private Semaphore semFree;
	private Semaphore semFull;
	private Integer item;

	public Producer(Queue<Integer> queueProd, int queueSize, Semaphore semFree, Semaphore semFull) {
		this.queue = queueProd;
		this.queueDimension = queueSize;
		this.semFree = semFree;
		this.semFull = semFull;
	}

	@Override

	public void run() {
		while (true) {
			System.out.println("I am producing");
			try {
				sleep(2000);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			item = produce();
			semFree.release(); //down
			enque(item);
			try {
				semFull.acquire();
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} //up
		}
	}


	private void enque(Integer item2) {
		queue.add(item2);
		
		
	}

	public Integer produce() {
		queue.add(1);
		queue.notifyAll();
		return item;
	}
}
