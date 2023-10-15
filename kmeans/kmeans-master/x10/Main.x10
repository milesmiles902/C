import x10.regionarray.Array;
import x10.compiler.Native;

public class Main {

	static val times = 100;

	public static def main(Rail[String]) {
		val xs = new Array[RichPoint](100000);

		/*Java json import
		val javaRead = new jsonRead();
		javaRead.initialize();
		for (i in 0..99999)
			xs(i) = new RichPoint(jsonRead.getNextX(), jsonRead.getNextY());
		*/

		/* C json import
		CJson.initialize();
		for (i in 0..99999)
				xs(i) = new RichPoint(CJson.getNextX(), CJson.getNextY());
		*/

		val beforeTime = System.currentTimeMillis();

		for (i in 1..times)
			KMeans.run(xs);


		val afterTime = System.currentTimeMillis();
		Console.OUT.println("Elapsed time is "+((afterTime-beforeTime)/times));
	}

}
