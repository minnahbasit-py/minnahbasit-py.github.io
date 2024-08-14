'use client';
import { useState, useEffect } from 'react'
import { Box, Stack, Typography, Button, Modal, TextField } from '@mui/material'
import { firestore } from '@/firebase'
import {
  collection,
  doc,
  getDocs,
  query,
  setDoc,
  deleteDoc,
  getDoc,
} from 'firebase/firestore'

// Styling for the page
const style = {
  position: 'absolute',
  top: '50%',
  left: '50%',
  transform: 'translate(-50%, -50%)',
  width: 400,
  bgcolor: '#FFF7E4', // Light cream background
  borderRadius: 12,
  boxShadow: '0px 10px 30px rgba(0, 0, 0, 0.1)',
  p: 4,
  display: 'flex',
  flexDirection: 'column',
  gap: 3,
}

export default function Home() {
  const [inventory, setInventory] = useState([])
  const [open, setOpen] = useState(false)
  const [itemName, setItemName] = useState('')

  const updateInventory = async () => {
    const snapshot = query(collection(firestore, 'inventory'))
    const docs = await getDocs(snapshot)
    const inventoryList = []
    docs.forEach((doc) => {
      inventoryList.push({ name: doc.id, ...doc.data() })
    })
    setInventory(inventoryList)
  }

  useEffect(() => {
    updateInventory();
  }, [])

  const addItem = async (item) => {
    const docRef = doc(collection(firestore, 'inventory'), item)
    const docSnap = await getDoc(docRef)
    if (docSnap.exists()) {
      const { quantity } = docSnap.data()
      await setDoc(docRef, { quantity: quantity + 1 })
      setInventory(prevInventory =>
        prevInventory.map(inv => inv.name === item ? { ...inv, quantity: quantity + 1 } : inv)
      )
    } else {
      await setDoc(docRef, { quantity: 1 })
      setInventory([...inventory, { name: item, quantity: 1 }])
    }
    handleClose()
  }

  const removeItem = async (item) => {
    const docRef = doc(collection(firestore, 'inventory'), item)
    const docSnap = await getDoc(docRef)
    if (docSnap.exists()) {
      const { quantity } = docSnap.data()
      if (quantity === 1) {
        await deleteDoc(docRef)
        setInventory(inventory.filter(inv => inv.name !== item))
      } else {
        await setDoc(docRef, { quantity: quantity - 1 })
        setInventory(prevInventory =>
          prevInventory.map(inv => inv.name === item ? { ...inv, quantity: quantity - 1 } : inv)
        )
      }
    }
  }

  const handleOpen = () => setOpen(true)
  const handleClose = () => setOpen(false)

  return (
    <Box
      width="100vw"
      height="100vh"
      display={'flex'}
      justifyContent={'center'}
      alignItems={'center'}
      bgcolor={'#FFDDE2'} // Soft pastel pink background
      padding={4}
    >
      <Typography variant="h3" color="#6B4226" fontFamily="'Fredoka One', sans-serif" gutterBottom>
        Inventory Management
      </Typography>

      <Modal
        open={open}
        onClose={handleClose}
        aria-labelledby="modal-modal-title"
        aria-describedby="modal-modal-description"
      >
        <Box sx={style}>
          <Typography id="modal-modal-title" variant="h5" color="#6B4226" fontFamily="'Fredoka One', sans-serif">
            Add Item
          </Typography>
          <Stack width="100%" direction={'row'} spacing={2}>
            <TextField
              id="outlined-basic"
              label="Item"
              variant="outlined"
              fullWidth
              value={itemName}
              onChange={(e) => setItemName(e.target.value)}
              sx={{
                '& .MuiOutlinedInput-root': {
                  borderRadius: 8, // Rounded corners for text field
                },
              }}
            />
            <Button
              variant="contained"
              onClick={() => {
                addItem(itemName)
                setItemName('')
              }}
              sx={{
                backgroundColor: '#FFB3BA', // Pastel pink color
                '&:hover': {
                  backgroundColor: '#FF9AA2', // Slightly darker on hover
                },
                borderRadius: 12, // Rounded corners
                fontFamily: "'Fredoka One', sans-serif",
              }}
            >
              Add
            </Button>
          </Stack>
        </Box>
      </Modal>

      <Button
        variant="contained"
        onClick={handleOpen}
        sx={{
          backgroundColor: '#FFB3BA', // Pastel pink color
          '&:hover': {
            backgroundColor: '#FF9AA2', // Slightly darker on hover
          },
          borderRadius: 12, // Rounded corners
          padding: '10px 20px',
          fontSize: '16px',
          fontFamily: "'Fredoka One', sans-serif",
        }}
      >
        Add New Item
      </Button>

      <Box border={'1px solid #DDDDDD'} width="800px" borderRadius={12} overflow="hidden" bgcolor="#FFF7E4">
        <Box
          height="100px"
          bgcolor={'#FFB3BA'}
          display={'flex'}
          justifyContent={'center'}
          alignItems={'center'}
        >
          <Typography variant={'h4'} color={'#6B4226'} textAlign={'center'} fontFamily="'Fredoka One', sans-serif">
            Inventory Items
          </Typography>
        </Box>

        <Stack
          width="100%"
          height="300px"
          spacing={2}
          padding={2}
          overflow={'auto'}
          sx={{ backgroundColor: '#ffffff' }}
        >
          {inventory.map(({ name, quantity }) => (
            <Box
              key={name}
              width="100%"
              minHeight="150px"
              display={'flex'}
              justifyContent={'space-between'}
              alignItems={'center'}
              bgcolor={'#F8E9E9'}
              paddingX={5}
              borderRadius={8}
              boxShadow="0px 2px 8px rgba(0, 0, 0, 0.1)"
            >
              <Typography variant={'h5'} color={'#6B4226'} textAlign={'center'} fontFamily="'Fredoka One', sans-serif">
                {name.charAt(0).toUpperCase() + name.slice(1)}
              </Typography>
              <Typography variant={'h5'} color={'#6B4226'} textAlign={'center'} fontFamily="'Fredoka One', sans-serif">
                Quantity: {quantity}
              </Typography>
              <Button
                variant="contained"
                onClick={() => removeItem(name)}
                sx={{
                  backgroundColor: '#FFB3BA', // Pastel pink color for remove button
                  '&:hover': {
                    backgroundColor: '#FF9AA2', // Darker pink on hover
                  },
                  borderRadius: 12, // Rounded corners
                  fontFamily: "'Fredoka One', sans-serif",
                }}
              >
                Remove
              </Button>
            </Box>
          ))}
        </Stack>
      </Box>
    </Box>
  )
}
