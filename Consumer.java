package prodCons;

import java.util.Queue;

public class Consumer extends Thread {
	
	private Queue<Integer> queue;
	int queueDimension;
	public Consumer(Queue<Integer> queueCons, int queueSize) {
		this.queue = queueCons;
		this.queueDimension = queueSize;
	}

	@Override
	public void run(){
		while(true){
			synchronized(queue){
				while(queue.isEmpty()){
					System.out.println("Empty queue, WAIT!");
					try {
						queue.wait();
					} catch (InterruptedException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
				System.out.println("I am consuming");
				queue.remove();
				try {
					sleep(1000);
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
			
		}
		
	}

}
