

import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {


	public UrlValidatorTest(String testName) {
		super(testName);
	}



	public void testManualTest()
	{
		//You can use this function to implement your manual testing	   

	}


	public void testYourFirstPartition()
	{
		//You can use this function to implement your First Partition testing	   

	}

	public void testYourSecondPartition(){
		//You can use this function to implement your Second Partition testing	   

	}
	//You need to create more test cases for your Partitions if you need to 

	public void testIsValid()
	{
		System.out.println("----------------------------------------------------------");
		System.out.println("PROGRAMMING BASED TESTING");
		System.out.println("----------------------------------------------------------");
		System.out.println("\nNEGATIVE TEST CASES\n\n");
		
		UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		UrlValidator urlValNoFragments = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES + UrlValidator.NO_FRAGMENTS);
		UrlValidator urlValTwoSlashes = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES + UrlValidator.ALLOW_2_SLASHES);

		System.out.println("Test 1: return false if url is null");
		assertBooleanMatch(false, urlVal.isValid(null));

		System.out.println("Test 2: return false if url scheme is invalid");
		try {		   
			assertBooleanMatch(false, urlVal.isValid("htt://www.google.com/"));
		} catch (Error e) {
			System.out.println("ERROR: " + e + "\n\n");
		}

		System.out.println("Test 3: return false if the scheme is 'file', the url does not have "
				+ "an empty authority, and the authority contains ':'");
		try {		   
			assertBooleanMatch(false, urlVal.isValid("file://test:"));
		} catch (Error e) {
			System.out.println("ERROR: " + e + "\n\n");
		}

		System.out.println("Test 4: return false if the scheme is not 'file' and has an invalid"
				+ " authority and no RegExValidator provided");
		assertBooleanMatch(false, urlVal.isValid("http://"));

		System.out.println("Test 5: return false if the url has an invalid path");
		assertBooleanMatch(false, urlVal.isValid("http://www.google.com/^"));
		
		System.out.println("Test 6: return false if the url path starts with '/../'");
		assertBooleanMatch(false, urlVal.isValid("http://www.google.com/../test"));
		
		System.out.println("Test 7: return false if the url path is '/..'");
		assertBooleanMatch(false, urlVal.isValid("http://www.google.com/.."));
		
		System.out.println("Test 8: return false if the url path has '//' and ALLOW_2_SLASHES is turned off");
		assertBooleanMatch(false, urlVal.isValid("http://www.google.com//test"));
		
		System.out.println("Test 9: return false if the url query is an empty space");
		assertBooleanMatch(false, urlVal.isValid("http://www.google.com/test? ?"));
		
		System.out.println("Test 10: return false if the url has an invalid path");
		assertBooleanMatch(false, urlVal.isValid("http://www.google.com/^"));
		
		System.out.println("Test 11: return false if the url has a fragment but NO_FRAGMENTS is turned on");
		assertBooleanMatch(false, urlValNoFragments.isValid("http://www.google.com/test#fragment"));
				
		System.out.println("\n\n----------------------------------------------------------");
		System.out.println("POSITIVE TEST CASES\n\n");
		
		System.out.println("Test 12: return true if the url has a valid scheme of http");
		assertBooleanMatch(true, urlVal.isValid("http://www.google.com/"));
		
		System.out.println("Test 13: return true if the url has a valid scheme of https");
		try {		   
			assertBooleanMatch(true, urlVal.isValid("https://www.google.com/"));
		} catch (Error e) {
			System.out.println("ERROR: " + e + "\n\n");
		}
		
		System.out.println("Test 14: return true if the scheme is 'file' and has an empty authority");
		try {		   
			assertBooleanMatch(true, urlVal.isValid("file://"));
		} catch (Error e) {
			System.out.println("ERROR: " + e + "\n\n");
		}
		
		System.out.println("Test 15: return true if the scheme is 'file', does not have an empty authority, and does not contain ':'");
		try {		   
			assertBooleanMatch(true, urlVal.isValid("file://test"));
		} catch (Error e) {
			System.out.println("ERROR: " + e + "\n\n");
		}
		
		System.out.println("Test 16: return true if the url path has '//' and ALLOW_2_SLASHES is on");
		assertBooleanMatch(true, urlValTwoSlashes.isValid("http://www.google.com/test//file"));
	
		System.out.println("Test 17: return true if the url path has a fragment and NO_FRAGMENTS is off");
		assertBooleanMatch(true, urlVal.isValid("http://www.google.com/test#fragment"));
	
		System.out.println("\n\n----------------------------------------------------------");
		System.out.println("BOUNDARY TEST CASES\n\n");
		
		System.out.println("Test 18: return false if the url does not match a normal url path");
		assertBooleanMatch(false, urlVal.isValid("http::/what**<"));
		
		System.out.println("Test 19: return false if the url schema is not a real schema");
		try {		   
			assertBooleanMatch(false, urlVal.isValid("notreal://www.google.com"));
		} catch (Error e) {
			System.out.println("ERROR: " + e + "\n\n");
		}
		
		System.out.println("Test 18: return true if the url is long but valid");
		assertBooleanMatch(true, urlVal.isValid("http://smile.amazon.com/apb/page/ref=gbps_tit_s-5_5baf_057e0599?handlerName=OctopusDealLandingStream&deals=057e0599&marketplaceId=ATVPDKIKX0DER&showVariations=false&smid=A2EPN08Z0FPLG4&pf_rd_p=a7e1c818-e7bc-4318-ae47-1f5300505baf&pf_rd_s=slot-5&pf_rd_t=701&pf_rd_i=gb_main&pf_rd_m=ATVPDKIKX0DER&pf_rd_r=JTVAMPJV3T309CTGXW4W"));
		
	}

	private void assertBooleanMatch(boolean expected, boolean actual) {
		System.out.println("Expected: " + expected + "     Actual: " + actual);

		if(expected == actual) {
			System.out.println("Test passed!");
		} else {
			System.out.println("Test failed!");
		}
		System.out.print("\n\n");
	}

}
