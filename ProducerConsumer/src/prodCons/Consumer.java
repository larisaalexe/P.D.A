package prodCons;

import java.util.Queue;
import java.util.concurrent.Semaphore;

public class Consumer extends Thread {

	private Queue<Integer> queue;
	int queueDimension;
	private Semaphore semFree;
	private Semaphore semFull;
	private Consumer item;

	public Consumer(Queue<Integer> queueCons, int queueSize, Semaphore semFree, Semaphore semFull) {
		this.queue = queueCons;
		this.queueDimension = queueSize;
		this.semFree = semFree;
		this.semFull = semFull;
	}

	@Override
	public void run() {
		while (true) {
			try {
				semFull.acquire();
			} catch (InterruptedException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
			item = deque();
			semFree.release();
			consume(item);
			System.out.println("I am consuming");
			try {
				sleep(1000);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}

		}

	}


	private Consumer deque() {
		if(!queue.isEmpty()){
			queue.remove();
		}
		return item;
	}


	public Consumer consume(Consumer item2) {
		queue.remove();
		return item;
	}

}
