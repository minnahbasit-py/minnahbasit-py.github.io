// Import the functions you need from the SDKs you need
import { initializeApp } from "firebase/app";
import { getFirestore } from "firebase/firestore";
// TODO: Add SDKs for Firebase products that you want to use
// https://firebase.google.com/docs/web/setup#available-libraries

// Your web app's Firebase configuration
// For Firebase JS SDK v7.20.0 and later, measurementId is optional
const firebaseConfig = {
  apiKey: "AIzaSyAQYZirKtF8PRhJqTY1znBxZ_mDNBeiu5Y",
  authDomain: "inventory-management-app-a809e.firebaseapp.com",
  projectId: "inventory-management-app-a809e",
  storageBucket: "inventory-management-app-a809e.appspot.com",
  messagingSenderId: "1043722001289",
  appId: "1:1043722001289:web:9ee4fed775ae51feebdf58",
  measurementId: "G-NG2G1GSS6B"
};

// Initialize Firebase
const app = initializeApp(firebaseConfig);
const firestore = getFirestore(app);
export { firestore }
