
import { Home } from './pages/home.jsx'
import './App.css'
import './index.css'
import { BrowserRouter as Router, Route, Routes } from 'react-router-dom'
import { Layout } from './components/Layout.jsx'


function App() {
  return (

    
    <Router>
    <Layout> 
      <Routes>
        <Route path="/" element={<Home />} />
      </Routes>
      </Layout>
    </Router>
    

  )
}

export default App