import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.util.StringTokenizer;

/*
 * Template taken from @Petr (http://codeforces.com/profile/Petr)
 */
public class Main {
    public static void main(String[] args) {
        InputStream inputStream = System.in;
        OutputStream outputStream = System.out;
        InputReader in = new InputReader(inputStream);
        PrintWriter out = new PrintWriter(outputStream);

        example(in, out);
     
        out.close();
    }
    
    /* EXAMPLE
     * reads the triplet (int1, operator, int2), prints the value of (int1) operator (int2).
     */
    public static void example(InputReader in, PrintWriter out) {
        while(true) {
        	String ta = in.next();
        	String op = in.next();
        	String tb = in.next();
        	
        	if(ta != null) {
        		int a = Integer.parseInt(ta);
        		int b = Integer.parseInt(tb);
        		int res = 0;
        		if(op.equals("+")) {
        			res = a + b;
        		}
        		else if(op.equals("-")) {
        			res = a - b;
        		}
        		
        		out.printf("%d %s %d = %d\n", a, op, b, res);
        	}
        	else {
        		break;
        	}
        }
    }

    static class InputReader {
        public BufferedReader reader;
        public StringTokenizer tokenizer;

        public InputReader(InputStream stream) {
            reader = new BufferedReader(new InputStreamReader(stream), 32768);
            tokenizer = null;
        }

        /**
         * @return A token, each token is separated by white spaces or '\n'. Returns null in EOF.
         */
        public String next() {
            while (tokenizer == null || !tokenizer.hasMoreTokens()) {
                try {
                	final String line = reader.readLine();
                	if(line == null) {
                		return null;
                	}
                    tokenizer = new StringTokenizer(line);
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            }
            return tokenizer.nextToken();
        }

        public long nextLong() {
            return Long.parseLong(next());
        }

        public int nextInt() {
        	return Integer.parseInt(next());
        }
        
        public double nextDouble() {
        	return Double.parseDouble(next());
        }
    }
}
