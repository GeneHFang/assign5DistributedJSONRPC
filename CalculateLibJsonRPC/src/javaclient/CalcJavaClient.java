package ser321.jsonrpc;

import java.io.*;
import java.util.*;
import java.net.URL;
import org.json.JSONObject;
import org.json.JSONArray;

/**
 * Copyright (c) 2015 Tim Lindquist,
 * Software Engineering,
 * Arizona State University at the Polytechnic campus
 * <p/>
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation version 2
 * of the License.
 * <p/>
 * This program is distributed in the hope that it will be useful,
 * but without any warranty or fitness for a particular purpose.
 * <p/>
 * Please review the GNU General Public License at:
 * http://www.gnu.org/licenses/gpl-2.0.html
 * see also: https://www.gnu.org/licenses/gpl-faq.html
 * so you are aware of the terms and your rights with regard to this software.
 * Or, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,USA
 * <p/>
 * Purpose:
 * A Java class and main method demonstrating an approach to calling
 * JsonRpc methods.
 *
 * This software is meant to run on Debian Wheezy Linux
 * <p/>
 * Ser321 Principles of Distributed Software Systems
 * see http://pooh.poly.asu.edu/Ser321
 * @author Tim Lindquist (Tim.Lindquist@asu.edu) CIDSE - Software Engineering,
 *                       IAFSE, ASU at the Polytechnic campus
 * @date    July, 2015
 **/
public class CalcJavaClient extends Object implements Calculate {

   public String serviceURL;
   public JsonRpcRequestViaHttp server;
   public static int id = 0;

   public CalcJavaClient (String serviceURL) {
      this.serviceURL = serviceURL;
      try{
         this.server = new JsonRpcRequestViaHttp(new URL(serviceURL));
      }catch (Exception ex){
         System.out.println("Malformed URL "+ex.getMessage());
      }
   }

   private String packageCalcCall(String oper, double left, double right){
      JSONObject jsonObj = new JSONObject();
/*
 * the following code to create the array should, but does not work correctly
 * for doubles that are whole numbers.
 * That is, for + 2.0 3.0 it produces the json array [2,3]
 * To make the server see double/float values, roll my own to get [2.00,3.00]
 * This has the disadvantage that it removes any more than two places of accuracy,
 * but hey, its an class example.
      JSONArray anArr = new JSONArray();
      anArr.put(left);
      anArr.put(right);
      jsonObj.put("params",anArr);
 */
      jsonObj.put("jsonrpc","2.0");
      jsonObj.put("method",oper);
      jsonObj.put("id",++id);
      String almost = jsonObj.toString();
      String toInsert = ",\"params\":["+ String.format("%.2f", left)
                        + "," + String.format("%.2f", right) + "]";
      String begin = almost.substring(0,almost.length()-1);
      String end = almost.substring(almost.length()-1);
      String ret = begin + toInsert + end;
      return ret;
   }

   /**
    * Add two numbers
    * @return The sum
    */
   public double plus(double left, double right){
      double result = 0;
      try{
         String jsonStr = this.packageCalcCall("plus",left,right);
         //System.out.println("sending: "+jsonStr);
         String resString = server.call(jsonStr);
         //System.out.println("got back: "+resString);
         JSONObject res = new JSONObject(resString);
         result = res.optDouble("result");
      }catch(Exception ex){
         System.out.println("exception in rpc call to plus: "+ex.getMessage());
      }
      return result;
   }

   /**
    * Subtract two numbers
    * @return The difference
    */
   public double minus(double left, double right){
      double result = 0;
      try{
         String jsonStr = this.packageCalcCall("minus",left,right);
         String resString = server.call(jsonStr);
         JSONObject res = new JSONObject(resString);
         result = res.optDouble("result");
      }catch(Exception ex){
         System.out.println("exception in rpc call to plus: "+ex.getMessage());
      }
      return result;
   }

   /**
    * Multiply two numbers
    * @return The product
    */
   public double times(double left, double right){
      double result = 0;
      try{
         String jsonStr = this.packageCalcCall("times",left,right);
         String resString = server.call(jsonStr);
         JSONObject res = new JSONObject(resString);
         result = res.optDouble("result");
      }catch(Exception ex){
         System.out.println("exception in rpc call to plus: "+ex.getMessage());
      }
      return result;
   }

   /**
    * Divide two numbers
    * @return left / right
    */
   public double divide(double left, double right){
      double result = 0;
      try{
         String jsonStr = this.packageCalcCall("divide",left,right);
         String resString = server.call(jsonStr);
         JSONObject res = new JSONObject(resString);
         result = res.optDouble("result");
      }catch(Exception ex){
         System.out.println("exception in rpc call to plus: "+ex.getMessage());
      }
      return result;
   }

   /**
    * Get the service information.
    * @return The service information
    */
   public String serviceInfo(){
      return "Service information";
   }

   public static void main(String args[]) {
      try {
         String url = "http://127.0.0.1:8080/";
         if(args.length > 0){
            url = args[0];
         }
         CalcJavaClient cjc = new CalcJavaClient(url);
         BufferedReader stdin = new BufferedReader(
            new InputStreamReader(System.in));
         System.out.print("Enter end or {+|-|*|/} double double eg + 3 5 >");
         String inStr = stdin.readLine();
         StringTokenizer st = new StringTokenizer(inStr);
         String opn = st.nextToken();
         while(!opn.equalsIgnoreCase("end")) {
            if(opn.equalsIgnoreCase("+")){
               double result = cjc.plus(Double.parseDouble(st.nextToken()),
                                        Double.parseDouble(st.nextToken()));
               System.out.println("response: "+result);
            }else if (opn.equalsIgnoreCase("-")) {
               double result = cjc.minus(Double.parseDouble(st.nextToken()),
                                        Double.parseDouble(st.nextToken()));
               System.out.println("response: "+result);
            }else if (opn.equalsIgnoreCase("*")) {
               double result = cjc.times(Double.parseDouble(st.nextToken()),
                                        Double.parseDouble(st.nextToken()));
               System.out.println("response: "+result);
            }else if (opn.equalsIgnoreCase("/")) {
               double result = cjc.divide(Double.parseDouble(st.nextToken()),
                                        Double.parseDouble(st.nextToken()));
               System.out.println("response: "+result);
            }
            System.out.print("Enter end or {+|-|*|/} double double eg + 3 5 >");
            inStr = stdin.readLine();
            st = new StringTokenizer(inStr);
            opn = st.nextToken();
         }
      }catch (Exception e) {
         System.out.println("Oops, you didn't enter the right stuff");
      }
   }
}
