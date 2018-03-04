package prodCons;

import java.util.Queue;

public class Producer extends Thread {
	
	private Queue<Integer> queue;
	int queueDimension;
	
	public Producer(Queue<Integer> queueProd, int queueSize) {
		this.queue = queueProd;
		this.queueDimension = queueSize;
	}

	@Override

	public void run(){
		while(true){
			synchronized(queue){
			if(queue.size() == queueDimension){
				System.out.println("Queue is FULL,WAIT!");
				try {
					queue.wait();
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
			System.out.println("I am producing");	
			try {
				sleep(2000);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			}
		
		}

	}
}
